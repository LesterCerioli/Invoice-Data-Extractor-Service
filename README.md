# Invoice API

A C++ REST API that extracts invoice data from uploaded PDF files and sends the extracted information to a payment scheduler service.

## Project Overview

This project uses the Crow framework to create a REST API that allows users to upload PDF invoices. The API extracts the following information from the invoices:

- **Company Name**
- **Payment Value**
- **Due Date**

The extracted data is then sent to a service named Payment Scheduler, which is also built in C++ using CMake.

## Project Structure

![image](https://github.com/user-attachments/assets/258d7af4-aa0f-4d69-83d4-7bff88554f08)


## Dependencies

- **C++11 or higher**
- **CMake** (version 3.10 or higher)
- **Boost** (including `boost::asio` and `boost::beast`)
- **Poppler** (for PDF handling)
- **Crow** (for HTTP server)

## Installation

### Step 1: Install Dependencies

#### On Windows

1. **Boost**: Download and install from [Boost.org](https://www.boost.org/users/download/).
2. **Poppler**: Download Poppler binaries from a trusted source.
3. **CMake**: Download and install CMake from [cmake.org](https://cmake.org/download/).

#### On Ubuntu

You can install the necessary packages using:

```bash
sudo apt-get update
sudo apt-get install libboost-all-dev libpoppler-glib-dev cmake


### Step 2: Clone the Repository

Clone this repository to your local machine:

```bash
git clone https://your_repository_url.git
cd InvoiceAPI

## Step 3: Build the Project

1. Create a build directory:

   ```bash
   mkdir build
   cd build


2. Run CMake to configure the project:
   ```bash
   cmake ..

3. Build the project:
   ```bash
   cmake --build . --config Release

4. Running the API
   ##### after a successful build, you can run the application:
   ```bash
   ./InvoiceAPI




