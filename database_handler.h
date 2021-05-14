// github.com/A3st76/mysql_crypto. Source file under MIT license.

#pragma once

#include <iostream>
#include <mysql/jdbc.h>

#include "cargo_data.h"

class DatabaseHandler {
public:

	DatabaseHandler() {
		m_driver = std::unique_ptr<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());
	}

	void connect(const sql::SQLString& address, const sql::SQLString& login, const sql::SQLString& password) {

		m_con = std::unique_ptr<sql::Connection>(m_driver->connect(address, login, password));

		if (!m_con->isValid()) {
			throw std::runtime_error("Ошибка при подключении к базе данных");
		}

		m_con->setSchema("crypto");
		m_connected = true;
	}

	std::vector<std::string> get_tables() const {

		if (!m_connected) {
			throw std::runtime_error("Вы не подключены к базе данных");
		}

		std::vector<std::string> tables;

		try {
			std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(m_con->createStatement());
			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SHOW TABLES FROM crypto"));

			while (result->next()) {
				tables.push_back(result->getString("Tables_in_crypto"));
			}
		}
		catch (sql::SQLException& e) {
			std::cout << e.what() << std::endl;
		}
		return std::move(tables);
	}

	void insert_table_data(const std::string& table, const CargoData<std::string>& cargo) {

		if (!m_connected) {
			throw std::runtime_error("Вы не подключены к базе данных");
		}

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(m_con->createStatement());

		for (uint32_t i = 1; i < cargo.get_rows(); i++) {

			try {

				std::unique_ptr<sql::ResultSet> result;

				if (table == "daily") {
					result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
						"SELECT * FROM crypto." + table + " WHERE crypto." + table + ".id='" + cargo.get_data(i, 0) + "'" +
						" && crypto." + table + ".date='" + cargo.get_data(i, 1) + "'"));

					if (result->rowsCount() > 0) {
						continue;
					}
				} else {
					result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
						"SELECT * FROM crypto." + table + " WHERE crypto." + table + ".id='" + cargo.get_data(i, 0) + "'"));

					if (result->rowsCount() > 0) {

						this->update_table_data(table, cargo);
						continue;
					}
				}
			}
			catch (sql::SQLException& e) {
				std::cout << e.what() << std::endl;
			}
		
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
			catch (sql::SQLException& e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	void update_table_data(const std::string& table, const CargoData<std::string>& cargo) {

		if (!m_connected) {
			throw std::runtime_error("Вы не подключены к базе данных");
		}

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(m_con->createStatement());

		for (uint32_t i = 1; i < cargo.get_rows(); i++) {

			try {

				sql::SQLString query_str = "UPDATE crypto." + table + " SET ";

				for (uint32_t j = 0; j < cargo.get_cols(); j++) {
					query_str += "crypto." + table + "." + cargo.get_data(0, j) + "='" + cargo.get_data(i, j) + "',";
				}

				query_str.replace(query_str.length() - 1, 1, "");

				if (table == "daily") {
					query_str += " WHERE crypto." + table + ".id='" + cargo.get_data(i, 0) + "'" + " && crypto." + table + ".date='" + cargo.get_data(i, 1) + "'";
				} else {
					query_str += " WHERE crypto." + table + ".id='" + cargo.get_data(i, 0) + "'";
				}
				
				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(query_str));
			}
			catch (sql::SQLException& e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	void delete_data(const std::string& table, const CargoData<std::string>& source, const uint32_t row) {

		if (!m_connected) {
			throw std::runtime_error("Вы не подключены к базе данных");
		}

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(m_con->createStatement());

		try {

			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(
				"DELETE FROM crypto." + table + " WHERE id='" + source.get_data(row + 1, 0) + "'"));
		}
		catch (sql::SQLException& e) {
			std::cout << e.what() << std::endl;
		}
	}

	CargoData<std::string> get_filter_data(const CargoData<std::string>& filter_cargo) {

		if (!m_connected) {
			throw std::runtime_error("Вы не подключены к базе данных");
		}
	
		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(m_con->createStatement());

		CargoData<std::string> cargo(5);

		cargo.new_line();
		cargo.push_data("id");
		cargo.push_data("coin_name");
		cargo.push_data("market_value");
		cargo.push_data("market_cap");
		cargo.push_data("dominance");

		try {

			sql::SQLString query_str = "SELECT crypto.currency.* FROM crypto.currency \
				INNER JOIN crypto.mem_pool ON crypto.currency.id = crypto.mem_pool.id \
				INNER JOIN crypto.stats ON crypto.currency.id = crypto.stats.id WHERE ";

			for (uint32_t i = 0; i < filter_cargo.get_cols(); i++) {
				query_str += "crypto." + filter_cargo.get_data(0, i) + " >= '" + filter_cargo.get_data(1, i) + "' &&";
			}

			for (uint32_t i = 0; i < filter_cargo.get_cols(); i++) {

				if (std::stof(filter_cargo.get_data(2, i)) > 0) {
					query_str += "crypto." + filter_cargo.get_data(0, i) + " <= '" + filter_cargo.get_data(2, i) + "' &&";
				}
			}

			query_str.replace(query_str.length() - 2, 2, "");

			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(query_str));

			while (result->next()) {

				cargo.new_line();
				cargo.push_data(std::to_string(result->getInt(1)));
				cargo.push_data(result->getString(2));
				cargo.push_data(std::to_string(result->getDouble(3)));
				cargo.push_data(std::to_string(result->getInt64(4)));
				cargo.push_data(std::to_string(result->getDouble(5)));
			}
		}
		catch (sql::SQLException& e) {
			std::cout << e.what() << std::endl;
		}
		return cargo;
	}

	CargoData<std::string> get_coin_plot_data(const std::string& coin_name) {

		if (!m_connected) {
			throw std::runtime_error("Вы не подключены к базе данных");
		}

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(m_con->createStatement());

		uint32_t id = 0;

		try {

			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT id FROM crypto.currency WHERE \
			coin_name='" + coin_name + "'"));

			while (result->next()) {
				id = result->getInt(1);
			}

		}
		catch (sql::SQLException& e) {
			std::cout << e.what() << std::endl;
		}

		CargoData<std::string> cargo(3);

		cargo.new_line();
		cargo.push_data("date");
		cargo.push_data("market_value");
		cargo.push_data("transactions");

		try {

			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM crypto.daily WHERE \
			id='" + std::to_string(id) + "'"));

			while (result->next()) {

				cargo.new_line();
				cargo.push_data(result->getString(2));
				cargo.push_data(std::to_string(result->getDouble(3)));
				cargo.push_data(std::to_string(result->getUInt64(5)));
			}
		}
		catch (sql::SQLException& e) {
			std::cout << e.what() << std::endl;
		}
		return cargo;
	}

	/* std::tuple<std::string, float_t> call_test_func() {

		if (!m_connected) {
			throw std::runtime_error("Вы не подключены к базе данных");
		}

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(m_con->createStatement());

		std::string coin_name = "invalid";
		float_t coin_value = 0;

		try {

			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT crypto.get_coin_name_max_valued();"));
			
			if (result->next()) {
				coin_name = result->getString(1);
			}
		}
		catch (sql::SQLException& e) {
			std::cout << e.what() << std::endl;
		}

		try {

			std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT crypto.get_max_value();"));

			if (result->next()) {
				coin_value = result->getDouble(1);
			}
		}
		catch (sql::SQLException& e) {
			std::cout << e.what() << std::endl;
		}

		return { coin_name, coin_value };
	}*/

	CargoData<std::string> get_table_data(const std::string& name) {

		if (!m_connected) {
			throw std::runtime_error("Вы не подключены к базе данных");
		}

		std::unique_ptr<sql::Statement> stmt = std::unique_ptr<sql::Statement>(m_con->createStatement());

		if (name == "currency") {

			CargoData<std::string> cargo(5);

			cargo.new_line();
			cargo.push_data("id");
			cargo.push_data("coin_name");
			cargo.push_data("market_value");
			cargo.push_data("market_cap");
			cargo.push_data("dominance");

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
			catch (sql::SQLException& e) {
				std::cout << e.what() << std::endl;
			}
			return cargo;
		}
		else if(name == "stats") {

			CargoData<std::string> cargo(7);

			cargo.new_line();
			cargo.push_data("id");
			cargo.push_data("difficult");
			cargo.push_data("next_difficult");
			cargo.push_data("blockchain_size");
			cargo.push_data("blocks");
			cargo.push_data("transactions");
			cargo.push_data("outputs");

			try {
				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM crypto.stats"));

				while (result->next()) {

					cargo.new_line();
					cargo.push_data(std::to_string(result->getInt(1)));
					cargo.push_data(std::to_string(result->getUInt64(2)));
					cargo.push_data(std::to_string(result->getUInt64(3)));
					cargo.push_data(std::to_string(result->getDouble(4)));
					cargo.push_data(std::to_string(result->getInt(5)));
					cargo.push_data(std::to_string(result->getUInt64(6)));
					cargo.push_data(std::to_string(result->getUInt64(7)));
				}
			}
			catch (sql::SQLException& e) {
				std::cout << e.what() << std::endl;
			}
			return cargo;
		}
		else if (name == "mem_pool") {

			CargoData<std::string> cargo(4);

			cargo.new_line();
			cargo.push_data("id");
			cargo.push_data("transactions");
			cargo.push_data("tps");
			cargo.push_data("mem_size");

			try {
				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM crypto.mem_pool"));

				while (result->next()) {

					cargo.new_line();
					cargo.push_data(std::to_string(result->getInt(1)));
					cargo.push_data(std::to_string(result->getUInt64(2)));
					cargo.push_data(std::to_string(result->getDouble(3)));
					cargo.push_data(std::to_string(result->getUInt64(4)));
				}
			}
			catch (sql::SQLException& e) {
				std::cout << e.what() << std::endl;
			}
			return cargo;
		}
		else if (name == "daily") {

			CargoData<std::string> cargo(6);

			cargo.new_line();
			cargo.push_data("id");
			cargo.push_data("date");
			cargo.push_data("market_value");
			cargo.push_data("dominance");
			cargo.push_data("transactions");
			cargo.push_data("outputs");

			try {
				std::unique_ptr<sql::ResultSet> result = std::unique_ptr<sql::ResultSet>(stmt->executeQuery("SELECT * FROM crypto.daily"));

				while (result->next()) {

					cargo.new_line();
					cargo.push_data(std::to_string(result->getInt(1)));
					cargo.push_data(result->getString(2));
					cargo.push_data(std::to_string(result->getDouble(3)));
					cargo.push_data(std::to_string(result->getDouble(4)));
					cargo.push_data(std::to_string(result->getUInt64(5)));
					cargo.push_data(std::to_string(result->getUInt64(6)));
				}
			}
			catch (sql::SQLException& e) {
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

	std::unique_ptr<sql::mysql::MySQL_Driver> m_driver;
	std::unique_ptr<sql::Connection> m_con;
	bool m_connected;
};