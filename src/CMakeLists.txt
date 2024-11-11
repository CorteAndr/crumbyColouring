# Include checker, graphLoader libraries as subdirectories
add_subdirectory(checker)
add_subdirectory(graphLoader)
add_subdirectory(naiveCrumbyColouring)
add_subdirectory(prunedCrumbyColouring)

# Create executables
add_executable(naive naiveMain.cpp)
add_executable(pruned prunedMain.cpp)

# Link the libraries to the executables
target_link_libraries(naive PRIVATE graphLoader naiveCrumbyColouring)
target_link_libraries(pruned PRIVATE graphLoader prunedCrumbyColouring)