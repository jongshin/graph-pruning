target_sources( ${OUTPUT_LIBRARY}
PRIVATE
    Graph.cpp
    Generator.cpp
)
add_subdirectory(algorithm)


enable_testing()
add_subdirectory(test)