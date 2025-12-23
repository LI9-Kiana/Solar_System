# Include tests for remaining application parts
target_sources(testing PRIVATE
    ./earth_year.cpp
    ./gravitation.cpp
    ./inertia.cpp
    ./factory.cpp
    ./main.cpp
    ./print_visitor.cpp
    ./solar_system.cpp
)
