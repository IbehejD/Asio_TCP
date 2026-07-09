cmake_minimum_required(VERSION 3.16)
project(client_app LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include(CTest)

set(SOURCES
)

set(HEADERS

)

add_executable(client_app)
add_executable(server_app)

target_sources(client_app PRIVATE
    src/client.cpp
    ${SOURCES}
    ${HEADERS}
)

target_sources(server_app PRIVATE
    src/server.cpp
    ${SOURCES}
    ${HEADERS}
)

target_compile_features(client_app PUBLIC cxx_std_23)
target_include_directories(client_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(server_app PUBLIC cxx_std_23)
target_include_directories(server_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(asio REQUIRED CONFIG)

target_link_libraries(client_app asio::asio)
target_link_libraries(server_app asio::asio)


# if(BUILD_TESTING)
#     add_executable(dispatcher_tests)

#     target_sources(dispatcher_tests PRIVATE
#         tests/dispatcher_tests.cpp
#         ${SOURCES}
#         ${HEADERS}
#     )

#     target_include_directories(dispatcher_tests PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}/include
#     )

#     add_test(NAME dispatcher_tests COMMAND dispatcher_tests)
# endif()
