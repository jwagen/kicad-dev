#set( SOCI_CXX_C11 ON)
#set( SOCI_TESTS OFF)
#cmake_policy( SET CMP0063 OLD)
#add_subdirectory( soci )
# .cpp files are compiled with extra ${WSHADOW_FLAGS}
if( COMPILER_SUPPORTS_WSHADOW )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WSHADOW_FLAGS}")
endif()

add_subdirectory( idftools )
add_subdirectory( kicad-ogltest )

if( KICAD_USE_OCE OR KICAD_USE_OCC )
    add_subdirectory( kicad2step )
endif( KICAD_USE_OCE OR KICAD_USE_OCC )
