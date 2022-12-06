target_sources( ${OUTPUT_LIBRARY}
PRIVATE
    UnionFind.cpp
)

enable_testing()
add_subdirectory(test)