// github.com/A3st76/mysql_crypto. Source file under MIT license.

#pragma once

#include <iostream>
#include <mysql/jdbc.h>

#include "cargo_data.h"

class DatabaseHandler {
public:

	DatabaseHandler() {
		driver = std::unique_ptr<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());
	}

	void connect(const sql::SQLString& address) {
		//"tcp://176.114.130.215:3306"
		con = std::unique_ptr<sql::Connection>(driver->connect(address, "root", "191412dima"));

		if (!con->isValid()) {
			throw std::runtime_error("Ошибка при подключении к базе данных");
		}

		con->setSchema("crypto");
	}

	std::vector<std::string> get_tables() const {

		std::vector<std::string> tables;

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(con->createStatement());
		std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SHOW TABLES FROM crypto"));

		while (result->next()) {
			tables.push_back(result->getString("Tables_in_crypto"));
		}
		return std::move(tables);
	}

	CargoData<std::string> get_table_data(const std::string& name) {

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(con->createStatement());

		if (name == "currency") {

			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM crypto.currency"));
			
			CargoData<std::string> cargo(5);

			cargo.new_line();
			cargo.push_data("ID");
			cargo.push_data("Coin Name");
			cargo.push_data("Value");
			cargo.push_data("Market Cap");
			cargo.push_data("Dominance");

			while(result->next()) {

				cargo.new_line();
				cargo.push_data(std::to_string(result->getInt(1)));
				cargo.push_data(std::string(result->getString(2)));
				cargo.push_data(std::to_string(result->getInt(3)));
				cargo.push_data(std::to_string(result->getInt(4)));
				cargo.push_data(std::to_string(result->getInt(5)));

				std::cout << "id=" << result->getInt(1) << std::endl;
				std::cout << "coin_name=" << result->getString(2) << std::endl;
				std::cout << "value=" << result->getInt(3) << std::endl;
				std::cout << "market_cap=" << result->getInt(4) << std::endl;
				std::cout << "dominance=" << result->getDouble(5) << std::endl;
			}

			return cargo;
		}
		else {
			CargoData<std::string> cargo(5);
			return cargo;
		}
	}

private:

	std::unique_ptr<sql::mysql::MySQL_Driver> driver;
	std::unique_ptr<sql::Connection> con;
};