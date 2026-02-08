cmake_minimum_required(VERSION 3.10)
project(lw_button VERSION 1.0.0 LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 包含目录
include_directories(inc)

# 源文件
set(SOURCES
    src/lw_btn.c
)

# 创建静态库
add_library(lw_button STATIC ${SOURCES})

# 安装配置
install(TARGETS lw_button
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY inc/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# 如果存在测试文件，添加测试可执行文件
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/test.c")
    add_executable(lw_button_test test/test.c)
    target_link_libraries(lw_button_test lw_button)
    
    # 添加测试
    add_test(NAME lw_button_test COMMAND lw_button_test)
endif()

# 设置编译选项
target_compile_options(lw_button PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# 设置输出目录
set_target_properties(lw_button PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)