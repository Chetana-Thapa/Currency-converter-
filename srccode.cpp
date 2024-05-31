#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <curl/curl.h>
#include <rapidjson/document.h>

// Replace with your API key
const std::string API_KEY = "YOUR_API_KEY";
const std::string API_URL = "https://api.currencyscoop.com/v1/latest?api_key=" + API_KEY + "&base=";

// Function to handle HTTP response from API
size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
    s->append((char *)contents, size * nmemb);
    return size * nmemb;
}

// Function to fetch exchange rates from the API
std::map<std::string, double> fetchExchangeRates(const std::string& baseCurrency) {
    std::string url = API_URL + baseCurrency;
    std::string response;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    rapidjson::Document doc;
    doc.Parse(response.c_str());

    std::map<std::string, double> exchangeRates;
    if (doc.HasMember("response") && doc["response"].IsObject() && doc["response"].HasMember("rates")) {
        const rapidjson::Value& rates = doc["response"]["rates"];
        for (rapidjson::Value::ConstMemberIterator itr = rates.MemberBegin(); itr != rates.MemberEnd(); ++itr) {
            if (itr->value.IsNumber())
                exchangeRates[itr->name.GetString()] = itr->value.GetDouble();
        }
    }

    return exchangeRates;
}

// Function to convert currency
double convertCurrency(double amount, double rate) {
    return amount * rate;
}

int main() {
    std::string baseCurrency;
    std::cout << "Enter base currency code (e.g., USD, EUR): ";
    std::cin >> baseCurrency;

    std::map<std::string, double> exchangeRates = fetchExchangeRates(baseCurrency);

    if (exchangeRates.empty()) {
        std::cerr << "Failed to fetch exchange rates. Exiting...\n";
        return 1;
    }

    std::cout << "Exchange rates relative to " << baseCurrency << ":\n";
    for (const auto& pair : exchangeRates) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    std::string targetCurrency;
    double amount;
    std::cout << "\nEnter target currency code: ";
    std::cin >> targetCurrency;
    std::cout << "Enter amount to convert: ";
    std::cin >> amount;

    if (exchangeRates.find(targetCurrency) == exchangeRates.end()) {
        std::cerr << "Target currency not found. Exiting...\n";
        return 1;
    }

    double rate = exchangeRates[targetCurrency];
    double convertedAmount = convertCurrency(amount, rate);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << amount << " " << baseCurrency << " = " << convertedAmount << " " << targetCurrency << "\n";

    return 0;
}
