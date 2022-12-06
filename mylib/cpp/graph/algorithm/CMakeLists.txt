target_sources( ${OUTPUT_LIBRARY}
PRIVATE
    Traversal.cpp
    # Centrality.cpp
)

enable_testing()
add_subdirectory(test)