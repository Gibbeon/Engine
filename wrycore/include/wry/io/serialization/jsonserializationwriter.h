#pragma once

#include "wry/global.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace wry {
    namespace io {
		class JsonSerializationWriter {
		public:
			JsonSerializationWriter(json& json) : _json(json) {}
			~JsonSerializationWriter() {}

			template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
			bool_t write(gsl::czstring name, T& value) {
				_json[name] = value;

				return true;
			}

			template< typename T, std::enable_if_t<!std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr>
			bool_t write(gsl::czstring name, std::vector<T>& value) {
				_json[name] = value;

				return true;
			}

			template< typename T, std::enable_if_t<std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr >
			bool_t write(gsl::czstring name, T& value) {
				_json[name] = nullptr;
				value.serialize(JsonSerializationWriter(_json[name]));

				return true;
			}

			template< typename T, std::enable_if_t<std::is_base_of<ISerializable, T>::value, bool_t>* = nullptr>
			bool_t write(gsl::czstring name, std::vector<T>& value) {		
				for(auto& elem : value) {		
					_json[name].push_back(nullptr);	
					elem.serialize(JsonSerializationWriter(_json[name].back()));
				}
				
				return true;
			}

		private:
			json& _json;
		};
	}
}