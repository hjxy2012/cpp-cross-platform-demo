cmake_minimum_required(VERSION 3.16)
project(CrossPlatformCalculator VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 版本信息
if(DEFINED APP_VERSION)
    set(PROJECT_VERSION ${APP_VERSION})
    message(STATUS "Building version: ${APP_VERSION}")
endif()

# 编译器特定设置
if(MSVC)
    # Windows MSVC
    add_compile_options(/W4)
    # 静态链接运行时库
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # GCC 或 Clang
    add_compile_options(-Wall -Wextra -pedantic)
    
    # 🔥 关键修复：Windows MinGW静态链接配置
    if(WIN32)
        # Windows下使用MinGW时静态链接运行时库
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
        message(STATUS "Windows MinGW: 启用静态链接以避免运行时依赖")
    elseif(UNIX AND NOT APPLE)
        # Linux下静态链接
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif()
endif()

# 包含目录
include_directories(include)

# 源文件
set(SOURCES
    src/main.cpp
    src/calculator.cpp
)

set(HEADERS
    include/calculator.h
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 设置输出名称
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "calculator"
    VERSION ${PROJECT_VERSION}
)

# 传递版本信息到代码
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    APP_VERSION="${PROJECT_VERSION}"
)

# Windows特定设置
if(WIN32)
    # 设置控制台应用程序
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
    
    # 创建版本资源文件
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/version.rc"
        @ONLY
    )
    
    # 如果版本文件存在，添加到源文件
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in")
        target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/version.rc")
    endif()
endif()

# 安装规则
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    COMPONENT Runtime
)

# 安装文档
install(FILES 
    README.md
    DESTINATION .
    COMPONENT Documentation
    OPTIONAL
)

# CPack配置
set(CPACK_PACKAGE_NAME "CrossPlatformCalculator")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A cross-platform calculator built with C++ and CMake")
set(CPACK_PACKAGE_VENDOR "hjxy2012")
set(CPACK_PACKAGE_CONTACT "hjxy2012@gmail.com")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

# 平台特定的打包器
if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "Cross-Platform Calculator")
    set(CPACK_NSIS_PACKAGE_NAME "Calculator")
    set(CPACK_NSIS_CONTACT "hjxy2012@gmail.com")
    set(CPACK_NSIS_HELP_LINK "https://github.com/yourusername/cpp-cross-platform-demo")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/yourusername/cpp-cross-platform-demo")
    
elseif(APPLE)
    set(CPACK_GENERATOR "TGZ;DragNDrop")
    set(CPACK_DMG_FORMAT "UDBZ")
    set(CPACK_DMG_VOLUME_NAME "Calculator")
    
elseif(UNIX)
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
    
    # DEB包设置
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.17), libstdc++6 (>= 5.4.0)")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "CrossPlatform Calculator Team <hjxy2012@gmail.com>")
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Cross-Platform Calculator
 A simple calculator application built with C++ and CMake.
 Supports basic arithmetic operations: addition, subtraction, 
 multiplication, and division.")
    set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
    set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    
    # RPM包设置
    set(CPACK_RPM_PACKAGE_SUMMARY "Cross-platform calculator application")
    set(CPACK_RPM_PACKAGE_DESCRIPTION "A simple calculator application built with C++ and CMake")
    set(CPACK_RPM_PACKAGE_GROUP "Applications/Engineering")
    set(CPACK_RPM_PACKAGE_LICENSE "MIT")
endif()

# 设置组件
set(CPACK_COMPONENTS_ALL Runtime Documentation)
set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Calculator Application")
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "The main calculator executable")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Documentation")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION "README and license files")

# 包含CPack模块（必须在所有CPack变量设置之后）
include(CPack)