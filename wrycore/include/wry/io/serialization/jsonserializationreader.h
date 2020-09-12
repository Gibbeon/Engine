#pragma once

#include "wry/global.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace wry {
    namespace io {
        class JsonSerializationReader {
        public:
            JsonSerializationReader(json& json) : _json(json) {}
            ~JsonSerializationReader() {}

            template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
            bool_t read(T* value) {
                _json.get_to(*value);
                return true;
            }

            template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr>
            bool_t read(std::vector<T>* value) {
                for(auto& elem : _json) {
                    value->emplace_back(elem.get<T>());
                }

                return true;
            }

            template< typename T, std::enable_if_t<std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
            bool_t read(T* value) {
                *value = T(*this);
                return true;
            }

            template< typename T, std::enable_if_t<std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr>
            bool_t read(std::vector<T>* value) {
                for(auto& elem : _json) {
                    value->emplace_back(JsonSerializationReader(elem));
                }

                return true;
            }

            template<typename T> 
            bool_t read(gsl::czstring name, T* value) {
                if(_json.is_object()) {
                    return JsonSerializationReader(_json.at(name)).read(value);
                }
                return true;
            }

        private:
            json& _json;
        };
    }
}