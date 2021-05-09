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

	void connect(const sql::SQLString& address, const sql::SQLString& login, const sql::SQLString& password) {

		con = std::unique_ptr<sql::Connection>(driver->connect(address, login, password));

		if (!con->isValid()) {
			throw std::runtime_error("Ошибка при подключении к базе данных");
		}

		con->setSchema("crypto");
	}

	std::vector<std::string> get_tables() const {

		std::vector<std::string> tables;

		try {
			std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(con->createStatement());
			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SHOW TABLES FROM crypto"));

			while (result->next()) {
				tables.push_back(result->getString("Tables_in_crypto"));
			}
		}
		catch (sql::SQLException e) {
			std::cout << e.what() << std::endl;
		}
		return std::move(tables);
	}

	void insert_table_data(const std::string& table, const CargoData<std::string>& cargo) {

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(con->createStatement());

		for (uint32_t i = 1; i < cargo.get_rows(); i++) {
		
			try {

				sql::SQLString query_str = "INSERT INTO crypto." + table + " (";

				for (uint32_t j = 0; j < cargo.get_cols(); j++) {
					query_str += cargo.get_data(0, j) + ",";
				}

				query_str.replace(query_str.length() - 1, 1, ")");
				query_str += " VALUES (";

				for (uint32_t j = 0; j < cargo.get_cols(); j++) {
					query_str += "'" + cargo.get_data(i, j) + "',";
				}

				query_str.replace(query_str.length() - 1, 1, ")");

				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(query_str));
			}
			catch (sql::SQLException e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	void update_table_data(const std::string& table, const CargoData<std::string>& cargo) {

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(con->createStatement());

		for (uint32_t i = 1; i < cargo.get_rows(); i++) {

			try {

				sql::SQLString query_str = "INSERT INTO crypto." + table + "(";

				for (uint32_t j = 0; j < cargo.get_cols(); j++) {
					query_str += cargo.get_data(0, j) + ",";
				}

				query_str += ") VALUES (";

				for (uint32_t j = 0; j < cargo.get_cols(); j++) {
					query_str += "'" + cargo.get_data(i, j) + "',";
				}

				query_str = query_str.substr(query_str.length(), 1);
				query_str += ")";
				
				std::cout << query_str << std::endl;

				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
					"INSERT INTO crypto." + table + " (id,coin_name,value,market_cap,dominance) \
					VALUES ('" + cargo.get_data(i, 0) + "','" + cargo.get_data(i, 1) + "','" + cargo.get_data(i, 2) + "',\
					'" + cargo.get_data(i, 3) + "','" + cargo.get_data(i, 4) + "')")
					);
			}
			catch (sql::SQLException e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	CargoData<std::string> get_table_data(const std::string& name) {

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(con->createStatement());

		if (name == "currency") {

			CargoData<std::string> cargo(5);

			cargo.new_line();
			cargo.push_data("ID");
			cargo.push_data("Coin Name");
			cargo.push_data("Value");
			cargo.push_data("Market Cap");
			cargo.push_data("Dominance");

			try {
				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM crypto.currency"));

				while(result->next()) {

					cargo.new_line();
					cargo.push_data(std::to_string(result->getInt(1)));
					cargo.push_data(result->getString(2));
					cargo.push_data(std::to_string(result->getDouble(3)));
					cargo.push_data(std::to_string(result->getInt64(4)));
					cargo.push_data(std::to_string(result->getDouble(5)));
				}
			}
			catch (sql::SQLException e) {
				std::cout << e.what() << std::endl;
			}
			return cargo;
		}
		else if(name == "stats") {

			CargoData<std::string> cargo(6);

			cargo.new_line();
			cargo.push_data("ID");
			cargo.push_data("Difficult");
			cargo.push_data("Next Difficult");
			cargo.push_data("Blockchain Size");
			cargo.push_data("Blocks");
			cargo.push_data("Transactions");

			try {
				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM crypto.stats"));

				while (result->next()) {

					cargo.new_line();
					cargo.push_data(std::to_string(result->getInt(1)));
					cargo.push_data(std::to_string(result->getInt64(2)));
					cargo.push_data(std::to_string(result->getInt64(3)));
					cargo.push_data(std::to_string(result->getDouble(4)));
					cargo.push_data(std::to_string(result->getInt(5)));
					cargo.push_data(std::to_string(result->getInt(6)));
				}
			}
			catch (sql::SQLException e) {
				std::cout << e.what() << std::endl;
			}
			return cargo;
		}
		else if (name == "mem_pool") {

			CargoData<std::string> cargo(4);

			cargo.new_line();
			cargo.push_data("ID");
			cargo.push_data("Transactions");
			cargo.push_data("Transactions Per Sec");
			cargo.push_data("Memory Size");

			try {
				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM crypto.mem_pool"));

				while (result->next()) {

					cargo.new_line();
					cargo.push_data(std::to_string(result->getInt(1)));
					cargo.push_data(std::to_string(result->getInt(2)));
					cargo.push_data(std::to_string(result->getDouble(3)));
					cargo.push_data(std::to_string(result->getUInt64(4)));
				}
			}
			catch (sql::SQLException e) {
				std::cout << e.what() << std::endl;
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