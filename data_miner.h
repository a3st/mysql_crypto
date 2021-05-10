// github.com/A3st76/mysql_crypto. Source file under MIT license.

#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

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

    ~DataMiner() {
        ::curl_easy_cleanup(m_curl);
    }

    std::vector<std::map<std::string, std::string>> parse() {
        
		::curl_easy_setopt(m_curl, CURLOPT_URL, "https://api.blockchair.com/stats");
        ::curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
        ::curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0);
        ::curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0);

        std::string buffer;
        ::curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, buffer.data());
        ::curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, curl_write_func);

        CURLcode result = ::curl_easy_perform(m_curl);

        std::vector<std::map<std::string, std::string>> parse_data;

        if (result == CURLE_OK) {

            Json::Value root;
            Json::CharReaderBuilder reader_builder;
            std::string errs;

            const std::unique_ptr<Json::CharReader> reader(reader_builder.newCharReader());
            if (!reader->parse(buffer.c_str(), buffer.c_str() + buffer.size(), &root, &errs)) {
                throw std::runtime_error("Ошибка при чтение JSON");
            }

            auto data = root["data"];

            for (auto it_1 = data.begin(); it_1 != data.end(); ++it_1) {

                if (!data[it_1.name()]["data"].empty()) {

                    parse_data.push_back(std::map<std::string, std::string>());
                    parse_data.back()["coin_name"] = it_1.key().asString();
                    parse_data.back()["difficulty"] = "0";
                    parse_data.back()["next_difficulty_estimate"] = "0";
                    parse_data.back()["blockchain_size"] = "0";
                    parse_data.back()["blocks"] = "0";
                    parse_data.back()["transactions"] = "0";
                    parse_data.back()["market_price_usd"] = "0";
                    parse_data.back()["market_cap_usd"] = "0";
                    parse_data.back()["market_dominance_percentage"] = "0";
                    parse_data.back()["mempool_transactions"] = "0";
                    parse_data.back()["mempool_tps"] = "0";
                    parse_data.back()["mempool_size"] = "0";

                    //std::cout << "coin_name: " << it_1.key() << std::endl;
                } else {
                    continue;
                }

                auto data_2 = data[it_1.name()]["data"];

                for (auto it_2 = data_2.begin(); it_2 != data_2.end(); ++it_2) {

                    if (data_2[it_2.name()].isString() || data_2[it_2.name()].isIntegral() || data_2[it_2.name()].isNumeric() ||
                        data_2[it_2.name()].isDouble()) {

                        parse_data.back()[it_2.name()] = data_2[it_2.name()].asString();

                        //std::cout << it_2.key() << " " << data_2[it_2.name()].asString() << std::endl;
                    }
                }
                //std::cout << "_______________________" << std::endl;
            }

        } else {

            throw std::runtime_error("Blockchair.api не доступен в данный момент");
        }
        return parse_data;
	}

private:

	CURL* m_curl;
};