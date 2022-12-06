target_sources( ${OUTPUT_LIBRARY}
PRIVATE
    Pruning.cpp
)

enable_testing()
add_subdirectory(test)