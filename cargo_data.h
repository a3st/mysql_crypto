// github.com/A3st76/mysql_crypto. Source file under MIT license.

#pragma once

#include <tuple>
#include <sstream>

template<typename T>
class CargoData {
public:

	CargoData() {
	}

	void resize(const size_t cols) {
		m_data.clear();
		m_col_size = cols;
		m_cur = 0;
	}

	CargoData(const size_t col_size) : m_col_size(col_size) {
	}

	void new_line() {

		m_data.push_back(std::vector<T>(m_col_size));
		m_cur = 0;
	}

	void push_data(const T& data) {

		if (m_cur > m_col_size) {
			throw std::runtime_error("CargoData out of range");
		}

		m_data.back()[m_cur] = data;
		m_cur++;
	}

	void set_data(const uint32_t row, const uint32_t col, const T& data) {
		m_data[row][col] = data;
	}

	T get_data(const uint32_t row, const uint32_t col) const {
		return m_data[row][col];
	}

	size_t get_cols() const {
		return m_col_size;
	}

	size_t get_rows() const {
		return m_data.size();
	}

private:

	std::vector<
		std::vector<T>
	> m_data;

	size_t m_col_size;
	size_t m_cur;
};