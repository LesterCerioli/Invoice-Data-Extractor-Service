cmake_minimum_required(VERSION 3.10)
project(InvoiceAPI)

set(CMAKE_CXX_STANDARD 17)

# Add Crow library (single header version)
include_directories(third_party)

# Find and link libraries (assuming Poppler for PDF parsing)
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER REQUIRED poppler-glib)

include_directories(${POPPLER_INCLUDE_DIRS})

# Add source files
add_executable(InvoiceAPI
    src/main.cpp
    src/InvoiceExtractor.cpp
    src/PaymentScheduler.cpp
)

# Link Poppler for PDF handling
target_link_libraries(InvoiceAPI ${POPPLER_LIBRARIES})
