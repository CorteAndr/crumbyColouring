# Include checker, graphLoader libraries as subdirectories
add_subdirectory(checker)
add_subdirectory(graphLoader)
add_subdirectory(naiveCrumbyColouring)
add_subdirectory(prunedCrumbyColouring)

# Create executables
add_executable(naiveCount naiveCount.cpp)
add_executable(naiveSearch naiveSearch.cpp)
add_executable(prunedCount prunedCount.cpp)
add_executable(prunedSearch prunedSearch.cpp)


# Link the libraries to the executables
target_link_libraries(naiveCount PRIVATE graphLoader naiveCrumbyColouring)
target_link_libraries(naiveSearch PRIVATE graphLoader naiveCrumbyColouring)
target_link_libraries(prunedCount PRIVATE graphLoader prunedCrumbyColouring)
target_link_libraries(prunedSearch PRIVATE graphLoader prunedCrumbyColouring)