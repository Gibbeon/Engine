find_package(gsl-lite CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC gsl::gsl-lite gsl::gsl-lite-v0 gsl::gsl-lite-v1)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json nlohmann_json::nlohmann_json)