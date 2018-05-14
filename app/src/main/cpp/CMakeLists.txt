cmake_minimum_required(VERSION 3.4.1)


#用于生成单独的so
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

include_directories( utils)

#自动查找目录中的源文件，并加入编译
aux_source_directory(${CMAKE_SOURCE_DIR} src_dir1)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils src_dir2)
set(SRC_LIST ${src_dir1} ${src_dir2} )

add_library( nativeProcess
             SHARED
             ${SRC_LIST}
              )


target_link_libraries(nativeProcess
                       log )
