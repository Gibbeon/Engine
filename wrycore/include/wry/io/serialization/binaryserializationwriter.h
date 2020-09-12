#pragma once

#include "wry/global.h"

namespace wry {
    namespace io {
        class BinarySerializationWriter {
        public:
            BinarySerializationWriter(Stream& stream) : _stream(stream) {
                _stream.reset();
            }

            //template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
            bool_t write(gsl::czstring name, std::string& value) {
                size_t len = value.length();
                _stream.write(&len, sizeof(size_t));
                _stream.write(value.data(), len);
                return true;
            }

            template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
            bool_t write(gsl::czstring name, T& value) {
                _stream.write(&value, sizeof(T));
                //_json.get_to(*value);
                return true;
            }

            template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr>
            bool_t write(gsl::czstring name, std::vector<T>& value) {	
                size_t size = value.size();	
                _stream.write(&size, sizeof(size_t));

                for(auto& elem : value) {
                    _stream.write(&elem, sizeof(T));
                }

                return true;
            }

            template< typename T, std::enable_if_t<std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
            bool_t write(gsl::czstring name, T& value) {
                value.serialize(*this);
                return true;
            }

            template< typename T, std::enable_if_t<std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr>
            bool_t write(gsl::czstring name, std::vector<T>& value) {
                size_t size = value.size();	
                _stream.write(&size, sizeof(size_t));

                for(auto& elem : value) {		
                    elem.serialize(*this);
                }

                return true;
            }

        private:
            Stream& _stream;
        };
    }
}