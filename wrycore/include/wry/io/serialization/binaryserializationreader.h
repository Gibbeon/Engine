#pragma once

#include "wry/global.h"
#include "wry/io/serialization/serializable.h"
#include "wry/io/stream.h"

namespace wry {
    namespace io {
        class BinarySerializationReader {
        public:
            BinarySerializationReader(Stream& stream) : _stream(stream) {}
            ~BinarySerializationReader() {}

            //template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
            bool_t read(std::string* value) {
                size_t len = 0;
                _stream.read(&len, sizeof(size_t));
                value->resize(len);
                _stream.read(value->data(), len);
                //_json.get_to(*value);
                return true;
            }

            template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
            bool_t read(T* value) {
                _stream.read(value, sizeof(T));
                //_json.get_to(*value);
                return true;
            }

            template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr>
            bool_t read(std::vector<T>* value) {
                size_t size = 0;		
                _stream.read(&size, sizeof(size_t));

                for(size_t index = 0; index < size; index++) {
                    auto& item = value->emplace_back();
                    _stream.read(&item, sizeof(T));
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
                size_t size = 0;		
                _stream.read(&size, sizeof(size_t));

                for(size_t index = 0; index < size; index++) {
                    value->emplace_back(*this);
                }

                return true;
            }

            template<typename T> 
            bool_t read(gsl::czstring name, T* value) {
                return read(value);
            }

        private:
            Stream& _stream;
        };
    }
}
