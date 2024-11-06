# Include checker, graphLoader libraries as subdirectories
add_subdirectory(checker)
add_subdirectory(graphLoader)

# Create executables
add_executable(naiveCrumbyColouring naiveCrumbyColouring.cpp)
add_executable(prunedCrumbyColouring prunedCrumbyColouring.cpp)

# Link the libraries to the executables
target_link_libraries(naiveCrumbyColouring PRIVATE checker graphLoader)
target_link_libraries(prunedCrumbyColouring PRIVATE checker graphLoader)