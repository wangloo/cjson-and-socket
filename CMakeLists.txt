cmake_minimum_required(VERSION 3.16)
project (cpp)


include_directories(${PROJECT_SOURCE_DIR}/cJSON)

aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/cJSON SRC_CJSON)
add_executable (demo ${SRC_LIST} ${SRC_CJSON})			# 寻找源文件来编译可执行文件

# target_link_libraries(test5 
# 	${PROJECT_SOURCE_DIR}/lib/libadd.a) 
