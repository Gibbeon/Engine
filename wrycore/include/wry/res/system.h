#pragma once

#include "wry/global.h"

#include <fstream>
#include <thread>
#include <chrono>

namespace wry {
    namespace res {
        class Entity;
        class TypeResolver {
            struct Function {
                virtual ~Function() { }
            };

            // Derived class template for functions with a particular signature.
            template <typename T>
            struct BasicFunction : Function {
                std::function<T> function;
                BasicFunction(std::function<T> function) : function(function) { }
            };

        public:
            template<typename TReturn, typename ...TArgs>
            void add(std::string type, std::function<TReturn(TArgs...)> command) {
                _types.insert_or_assign(type,
                    std::move(std::shared_ptr<Function>(new BasicFunction<TReturn(TArgs...)>(std::function<TReturn(TArgs...)>(command)))));
            }

            template<typename TReturn, typename ...TArgs>
            vptr_t create(std::string type, TArgs&... args) {
                std::function<TReturn(TArgs&...)> fn = ((BasicFunction<TReturn(TArgs...)>*)(_types.at(type).get()))->function;
                return (vptr_t)fn(std::forward<TArgs>(args)...);
                return nullptr;
            }

        private:
            std::unordered_map<std::string, std::shared_ptr<Function>> _types;        
        };

        class Resource {
        public:
            Resource(const Resource&& parent) : _resolver(parent._resolver) {                
                this->_type = parent._type;
                this->_name = parent._name;
                this->_this = parent._this;
            }

            Resource(const Resource & parent)  : _resolver(parent._resolver) {                
                this->_type = parent._type;
                this->_name = parent._name;
                this->_this = parent._this;
            }


            Resource(std::string name, std::string type, TypeResolver& resolver) :
                _name(name),
                _type(type), 
                _this(nullptr),
                _resolver(resolver)
            {
            }

            template <typename Archive>
            Resource(Archive& context, TypeResolver& resolver) : 
                _resolver(resolver),
                _this(nullptr)
            {
                load(context);
            }

            void operator =(const Resource& parent) {
                this->_resolver = parent._resolver;
                this->_type = parent._type;
                this->_name = parent._name;
                this->_this = parent._this;
            }

            template <typename Archive>
            void load(Archive& context) {
                if(_this) this->destroy();

                context.read("name", &_name);
                context.read("type", &_type);

                _this = _resolver.create<vptr_t>(_type, context);
            }

            void destroy() {
                //_resolver.free(_this);
            }

            vptr_t get() {
                return _this;
            }

            std::string name() {
                return _name;
            }

        private:       
            TypeResolver& _resolver;

            std::string _name;
            std::string _type;

            vptr_t _this;
        };

        template<typename T>
        class ref_t {
        public:
            ref_t(Resource* pres = nullptr) : _res(pres) {}
            ref_t(Resource& res) : _res(&res) {
                
            }

            ref_t(Resource&& res) : _res(&res) {
                
            }


            ref_t<T> operator =(const ref_t<T> & parent) {
                return ref_t<T>(parent._res);
            }

            T* operator->() { return get(); }
            operator T* () { return get(); }

            T* get() { return (T*)_res->get(); }
            Resource& resource() { return *_res; } 
        private:
            Resource* _res;
        };

        class Repository {
        public:
        ~Repository() {
            if(_thread.joinable())
            {
                _fw.stop();
                _thread.join();
            }
        }

            Repository(const Repository&& parent) : 
                _resolver(parent._resolver),
                _path(parent._path),                
                _fw{parent._path, std::chrono::milliseconds(500)}
            {          

                _thread = std::thread([&](Repository* _this)-> void {    

                    _fw.start([&] (std::string path_to_watch, wry::io::FileStatus status) -> void {
                        if(!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != wry::io::FileStatus::erased) {
                            return;
                        }

                        switch(status) {
                            case wry::io::FileStatus::created:
                                std::cout << "File created: " << path_to_watch << '\n';
                                break;
                            case wry::io::FileStatus::modified:
                                _this->load(path_to_watch);
                                std::cout << "File modified: " << path_to_watch << '\n';
                                break;
                            case wry::io::FileStatus::erased:
                                std::cout << "File erased: " << path_to_watch << '\n';
                                break;
                            default:
                                std::cout << "Error! Unknown file status.\n";
                        }
                    });
                }, this);

                _resources = parent._resources;
            }

            //Move Assignment Operator
            Repository & operator=(Repository && obj)
            {
                std::cout << "Move Assignment is called" << std::endl;
                //if (_thread.joinable())
                //    _thread.join();
                //_thread = std::move(obj._thread);
                return *this;
            }

            //Delete the copy constructor
            Repository(const Repository&) = delete;
            //Delete the Assignment opeartor
            Repository& operator=(const Repository&) = delete;

            Repository(std::string path, TypeResolver& resolver) : 
                _resolver(resolver), 
                _path(path), 
                _fw{path, std::chrono::milliseconds(500)}
            {

                load(path);
                _thread = std::thread([&](Repository* _this)-> void {   
                    _fw.start([&] (std::string path_to_watch, wry::io::FileStatus status) -> void {
                        if(!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != wry::io::FileStatus::erased) {
                            return;
                        }

                        switch(status) {
                            case wry::io::FileStatus::created:
                                std::cout << "File created: " << path_to_watch << '\n';
                                break;
                            case wry::io::FileStatus::modified:
                                _this->load(path_to_watch);
                                std::cout << "File modified: " << path_to_watch << '\n';
                                break;
                            case wry::io::FileStatus::erased:
                                std::cout << "File erased: " << path_to_watch << '\n';
                                break;
                            default:
                                std::cout << "Error! Unknown file status.\n";
                        }
                    });
                }, this);
            }

            template<typename T>
            ref_t<T>      find(std::string res) {
                //Resource ress("non", "non", _resolver);
                return ref_t<T>(_resources.at(res));
            }

        private:            
            void        load(std::string path) {
                std::ifstream i(path);
                if(!i) throw;
                json j;
                i >> j;

                //if(_resources.find())
                Resource res = Resource(wry::io::JsonSerializationReader(j), _resolver);
                if(_resources.find(res.name()) != _resources.end()) {
                    _resources.at(res.name()).load(wry::io::JsonSerializationReader(j));
                } else {
                    _resources.emplace(res.name(), Resource(wry::io::JsonSerializationReader(j), _resolver));
                }
                //
            }

            std::string _path;
            std::thread     _thread;
            TypeResolver&   _resolver;
            wry::io::FileWatcher _fw;
            std::unordered_map<std::string, Resource> _resources;
        };

        class System {
        public:            
            void mount(std::string path, TypeResolver& resolver) {
                if(std::filesystem::is_regular_file(path)) {
                    _repositories.emplace(path, Repository(path, resolver));
                }

                if(std::filesystem::is_directory(path)) {
                    for(auto& p: std::filesystem::directory_iterator(path)) {
                        mount(p.path().string(), resolver);
                    }
                }
            }

            retval_t<void> unmount(std::string string) {
                // if it's a path, do all files in the path
                // if it's a file, do just that file
            }

            template<typename T>
            ref_t<T> find(std::string res) {
                for(auto& kvp : _repositories) {
                    return kvp.second.find<T>(res);
                }

                return ref_t<T>();
            }

        private:
            std::unordered_map<std::string, Repository> _repositories;
        };
    }
}