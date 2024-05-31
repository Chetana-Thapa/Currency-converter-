# Currency Converter

This is a simple currency converter program written in C++. It allows users to convert between different currencies using the latest exchange rates fetched from an online API.

## Features

- Fetches the latest exchange rates from an API
- Supports conversion between various currencies
- Simple and easy-to-use command-line interface

## Requirements

- C++ compiler (supporting C++11)
- cURL library (libcurl)
- RapidJSON library

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/currency-converter.git
    ```

2. Navigate to the project directory:

    ```bash
    cd currency-converter
    ```

3. Compile the program:

    ```bash
    g++ -std=c++11 -o currency_converter currency_converter.cpp -lcurl -lrapidjson
    ```

## Usage

1. Obtain an API key from a currency exchange rate provider (e.g., CurrencyScoop).
2. Replace `"YOUR_API_KEY"` in the `currency_converter.cpp` file with your actual API key.
3. Run the program:

    ```bash
    ./currency_converter
    ```

4. Follow the on-screen instructions to perform currency conversion.

## Example

