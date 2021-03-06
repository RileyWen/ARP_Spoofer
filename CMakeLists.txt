cmake_minimum_required(VERSION 3.10)
project(arp-net-speed-controller)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

include(CMake-Modules/FindPCAP.cmake)
include(CMake-Modules/FindCurses.cmake)

add_executable(arp-net-speed-controller main.cpp
        arp_spoofer_lib/headers/net_structure.h
        arp_spoofer_lib/sources/AdapterQuery.cpp arp_spoofer_lib/headers/AdapterQuery.h
        arp_spoofer_lib/sources/net_structure.cpp arp_spoofer_lib/sources/ARPSpoofing.cpp
        arp_spoofer_lib/headers/ARPSpoofing.h arp_spoofer_lib/sources/PacketHandler.cpp
        arp_spoofer_lib/headers/PacketHandler.h
        arp_spoofer_lib/sources/ByteCounter.cpp
        arp_spoofer_lib/headers/ByteCounter.h
        concurrent_queue/headers/concurrent_queue.h
        concurrent_queue/headers/semaphore.h
        concurrent_queue/sources/semaphore.cpp
        ncurses_gui/sources/StatusBar.cpp ncurses_gui/headers/StatusBar.h
        ncurses_gui/sources/CommandLineArgParsing.cpp ncurses_gui/headers/CommandLineArgParsing.h)

target_link_libraries(arp-net-speed-controller ${PCAP_LIBRARY} ${CURSES_LIBRARY})

SET(CMAKE_CXX_FLAGS -pthread)