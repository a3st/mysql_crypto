// github.com/A3st76/mysql_crypto. Source file under MIT license.

#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

inline size_t curl_write_func(char* data, size_t size, size_t nmemb, std::string* buffer) {
    size_t result = 0;

    if (buffer != nullptr) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

class DataMiner {
public:

	DataMiner() {
	
		m_curl = ::curl_easy_init();
	}

	void parse() {

		::curl_easy_setopt(m_curl, CURLOPT_URL, "https://api.blockchair.com/stats");
        ::curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
        ::curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0);
        ::curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0);

        std::string buffer;
        ::curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, buffer.data());
        ::curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, curl_write_func);

        CURLcode result = ::curl_easy_perform(m_curl);

        ::curl_easy_cleanup(m_curl);

        if (result == CURLE_OK) {

            nlohmann::json json_reader = nlohmann::json::parse(buffer);

            auto data_coin_name = json_reader["data"];

            for (auto it_coin_name = data_coin_name.begin(); it_coin_name != data_coin_name.end(); ++it_coin_name) {

                std::cout << "coin_name: " << it_coin_name.key() << std::endl;

                auto data_coin_data = it_coin_name.value();

                for (auto it_coin_data = data_coin_data.begin(); it_coin_data != data_coin_data.end(); ++it_coin_data) {

                    std::cout << "________________________________________" << std::endl;
                    auto data_coin_stat = it_coin_data.value();

                    for (auto it_coin_stat = data_coin_stat.begin(); it_coin_stat != data_coin_stat.end(); ++it_coin_stat) {
                        std::cout << it_coin_stat.key() << ": " << it_coin_stat.value() << std::endl;
                    }
                    std::cout << "________________________________________" << std::endl;
                }
            }

        } else {
            std::cout << "Not Ok" << std::endl;
        }
	}

private:

	CURL* m_curl;
};