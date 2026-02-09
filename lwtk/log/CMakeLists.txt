cmake_minimum_required(VERSION 3.10)
project(lw_log VERSION 1.0.0 LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 创建静态库
add_library(lw_log STATIC
    src/lw_log.c
)

# 设置头文件目录
target_include_directories(lw_log PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# 创建测试可执行文件
add_executable(lw_log_test
    test/test.c
)

# 链接日志库到测试程序
target_link_libraries(lw_log_test lw_log)

# 设置测试程序的包含目录
target_include_directories(lw_log_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# 可选：安装目标
install(TARGETS lw_log
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES inc/lw_log.h
    DESTINATION include
)