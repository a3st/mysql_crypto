///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "frame.h"
#include "global.h"

///////////////////////////////////////////////////////////////////////////

void MyFrame1::on_db_connected() {

	auto tables = g_database_handler->get_tables();
	
	std::vector<wxString> tables_;
	for (uint32_t i = 0; i < tables.size(); i++) {
		tables_.push_back(tables[i].c_str());
	}

	m_comboBox_table->Set(tables_);
	m_comboBox_table->SetValue("currency");

	m_caches_cargos["currency"] = g_database_handler->get_table_data("currency");
	m_caches_cargos["mem_pool"] = g_database_handler->get_table_data("mem_pool");
	m_caches_cargos["stats"] = g_database_handler->get_table_data("stats");

	this->set_table_values_by_cargo(m_grid_table, m_caches_cargos["currency"]);
}

void MyFrame1::set_table_values_by_cargo(wxGrid* grid, const CargoData<std::string>& cargo) {

	if (grid->GetNumberRows() > 0) {
		grid->DeleteRows(0, grid->GetNumberRows());
	}
	if (grid->GetNumberCols() > 0) {
		grid->DeleteCols(0, grid->GetNumberCols());
	}

	grid->InsertCols(0, cargo.get_cols());
	grid->InsertRows(0, cargo.get_rows() - 1);

	for (uint32_t i = 0; i < cargo.get_cols(); i++) {
		grid->SetColLabelValue(i, cargo.get_data(0, i));
	}

	for (uint32_t i = 1; i < cargo.get_rows(); i++) {
		for (uint32_t j = 0; j < cargo.get_cols(); j++) {
			grid->SetCellValue(i - 1, j, cargo.get_data(i, j));
		}
	}
}

void MyFrame1::on_close(wxCloseEvent& event) {

	wxGetApp().Exit();
}

void MyFrame1::on_menu_sel_open_db(wxCommandEvent& event) {
	
	m_open_dial->ShowModal();
}

void MyFrame1::on_menu_sel_save_db(wxCommandEvent& event) {
	
	try {

		g_database_handler->update_table_data("currency", m_caches_cargos["currency"]);
		g_database_handler->update_table_data("mem_pool", m_caches_cargos["mem_pool"]);
		g_database_handler->update_table_data("stats", m_caches_cargos["stats"]);
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "Ошибка");
	}
}

void MyFrame1::on_menu_sel_update_db(wxCommandEvent& event) {

	m_comboBox_table->SetValue("currency");

	try {
		m_caches_cargos["currency"] = g_database_handler->get_table_data("currency");
		m_caches_cargos["mem_pool"] = g_database_handler->get_table_data("mem_pool");
		m_caches_cargos["stats"] = g_database_handler->get_table_data("stats");

		this->set_table_values_by_cargo(m_grid_table, m_caches_cargos["currency"]);
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "Ошибка");
	}
}

void MyFrame1::on_menu_sel_parse(wxCommandEvent& event) {

	auto values = g_data_miner->parse();

	CargoData<std::string> currency_data(5);
	currency_data.new_line();
	currency_data.push_data("id");
	currency_data.push_data("coin_name");
	currency_data.push_data("value");
	currency_data.push_data("market_cap");
	currency_data.push_data("dominance");

	uint32_t coin_idx = 0;

	for (uint32_t i = 0; i < values.size(); i++) {

		currency_data.new_line();
		currency_data.push_data(std::to_string(coin_idx));
		currency_data.push_data(values[i]["coin_name"]);
		currency_data.push_data(values[i]["market_price_usd"]);
		currency_data.push_data(values[i]["market_cap_usd"]);
		currency_data.push_data(values[i]["market_dominance_percentage"]);
		coin_idx++;
	}

	coin_idx = 0;

	CargoData<std::string> stats_data(6);
	stats_data.new_line();
	stats_data.push_data("id");
	stats_data.push_data("difficult");
	stats_data.push_data("next_difficult");
	stats_data.push_data("blockchain_size");
	stats_data.push_data("blocks");
	stats_data.push_data("transactions");

	for (uint32_t i = 0; i < values.size(); i++) {

		stats_data.new_line();
		stats_data.push_data(std::to_string(coin_idx));
		stats_data.push_data(values[i]["difficulty"]);
		stats_data.push_data(values[i]["next_difficulty_estimate"]);
		stats_data.push_data(values[i]["blockchain_size"]);
		stats_data.push_data(values[i]["blocks"]);
		stats_data.push_data(values[i]["transactions"]);
		coin_idx++;
	}

	coin_idx = 0;

	CargoData<std::string> mem_pool_data(4);
	mem_pool_data.new_line();
	mem_pool_data.push_data("id");
	mem_pool_data.push_data("transactions");
	mem_pool_data.push_data("transactions_time_s");
	mem_pool_data.push_data("mem_size");

	for (uint32_t i = 0; i < values.size(); i++) {

		mem_pool_data.new_line();
		mem_pool_data.push_data(std::to_string(coin_idx));
		mem_pool_data.push_data(values[i]["mempool_transactions"]);
		mem_pool_data.push_data(values[i]["mempool_tps"]);
		mem_pool_data.push_data(values[i]["mempool_size"]);
		coin_idx++;
	}

	try {
		g_database_handler->insert_table_data("stats", stats_data);
		g_database_handler->insert_table_data("mem_pool", mem_pool_data);
		g_database_handler->insert_table_data("currency", currency_data);
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "Ошибка");
	}
}

void MyFrame1::on_menu_sel_test_func(wxCommandEvent& event) {

	try {

		auto args = g_database_handler->call_test_func();
		::wxMessageBox("coin_name: " + std::get<0>(args) + "\ncoin_value: " + std::to_string(std::get<1>(args)), "call test_func");
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "Ошибка");
	}
}

void MyFrame1::on_menu_sel_help(wxCommandEvent& event) {

	::wxMessageBox(
		"Данная программа помогает получить информацию о криптовалютах.\n\
		Для работы программы требуется выделенный MySQL сервер и БД с определенными таблицами.\n\
		Таблицы и открытый код можно найти в репозитории, указанном ниже.\n\
		Для парсинга информации используется сервис Blockchair.\n\
		\n\
		Автор Dmitriy Lukovenko (github.com/A3st76)\n\
		MIT License.", "О программе"
	);
}

void MyFrame1::on_combobox_sel(wxCommandEvent& event) {

	std::string cur = m_comboBox_table->GetValue().c_str().AsChar();
	this->set_table_values_by_cargo(m_grid_table, m_caches_cargos[cur]);
}

void MyFrame1::on_button_click_apply_filters(wxCommandEvent& event) {

	try {

		float_t min_val = std::stof(m_textCtrl_min_val->GetValue().c_str().AsChar());
		float_t max_val = std::stof(m_textCtrl_max_val->GetValue().c_str().AsChar());

		int64_t min_blocks = std::stoll(m_textCtrl_min_blocks->GetValue().c_str().AsChar());
		int64_t max_blocks = std::stoll(m_textCtrl_max_blocks->GetValue().c_str().AsChar());

		int64_t min_mem = std::stoll(m_textCtrl_min_mem->GetValue().c_str().AsChar());
		int64_t max_mem = std::stoll(m_textCtrl_max_mem->GetValue().c_str().AsChar());

		try {
			m_caches_cargos["filter"] = g_database_handler->get_filter_data(min_val, max_val, min_blocks, max_blocks, min_mem, max_mem);
			this->set_table_values_by_cargo(m_grid_table, m_caches_cargos["filter"]);
		}
		catch (std::exception& e) {
			::wxMessageBox(e.what(), "Ошибка");
		}
	}
	catch(std::exception&) {
		::wxMessageBox("Недопустимые значения в фильтре", "Ошибка");
	}
}

void MyFrame1::on_button_click_clear_filters(wxCommandEvent& event) {

	std::string cur = m_comboBox_table->GetValue().c_str().AsChar();
	if (!m_caches_cargos.empty()) {
		this->set_table_values_by_cargo(m_grid_table, m_caches_cargos[cur]);
	}
	m_textCtrl_min_val->SetValue("0");
	m_textCtrl_max_val->SetValue("0");
	m_textCtrl_min_blocks->SetValue("0");
	m_textCtrl_max_blocks->SetValue("0");
	m_textCtrl_min_mem->SetValue("0");
	m_textCtrl_max_mem->SetValue("0");
}

MyFrame1::MyFrame1(const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(nullptr, wxID_ANY, title, pos, size, style) {
	
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

	m_menubar4 = new wxMenuBar(0);
	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem_open_db;
	m_menuItem_open_db = new wxMenuItem(m_menu2, wxID_ANY, wxString(wxT("Open DB")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuItem_open_db);

	wxMenuItem* m_menuItem_save_db;
	m_menuItem_save_db = new wxMenuItem(m_menu2, wxID_ANY, wxString(wxT("Save DB")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuItem_save_db);

	wxMenuItem* m_menuItem_update_db;
	m_menuItem_update_db = new wxMenuItem(m_menu2, wxID_ANY, wxString(wxT("Update DB")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuItem_update_db);

	m_menubar4->Append(m_menu2, wxT("SQL"));

	m_menu31 = new wxMenu();
	wxMenuItem* m_menuItem_parse;
	m_menuItem_parse = new wxMenuItem(m_menu31, wxID_ANY, wxString(wxT("Parse from Blockchair")), wxEmptyString, wxITEM_NORMAL);
	m_menu31->Append(m_menuItem_parse);

	wxMenuItem* m_menuItem_test_func;
	m_menuItem_test_func = new wxMenuItem(m_menu31, wxID_ANY, wxString(wxT("Test Functions")), wxEmptyString, wxITEM_NORMAL);
	m_menu31->Append(m_menuItem_test_func);

	m_menubar4->Append(m_menu31, wxT("Tools"));

	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem_help;
	m_menuItem_help = new wxMenuItem(m_menu3, wxID_ANY, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
	m_menu3->Append(m_menuItem_help);

	m_menubar4->Append(m_menu3, wxT("Help"));

	this->SetMenuBar(m_menubar4);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);


	bSizer1->Add(0, 5, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	m_grid_table = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), 0);

	// Grid
	m_grid_table->CreateGrid(5, 10);
	m_grid_table->EnableEditing(true);
	m_grid_table->EnableGridLines(true);
	m_grid_table->EnableDragGridSize(false);
	m_grid_table->SetMargins(0, 0);

	// Columns
	m_grid_table->EnableDragColMove(false);
	m_grid_table->EnableDragColSize(true);
	m_grid_table->SetColLabelSize(30);
	m_grid_table->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	m_grid_table->AutoSizeRows();
	m_grid_table->EnableDragRowSize(true);
	m_grid_table->SetRowLabelSize(80);
	m_grid_table->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	m_grid_table->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	bSizer8->Add(m_grid_table, 0, wxALL, 5);


	bSizer1->Add(bSizer8, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Current table"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer2->Add(m_staticText1, 0, wxALL, 5);

	m_comboBox_table = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	bSizer2->Add(m_comboBox_table, 0, wxALL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Filters"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	m_staticText2->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	bSizer2->Add(m_staticText2, 0, wxALL, 5);

	m_button_apply_filters = new wxButton(this, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button_apply_filters, 0, wxALL, 5);

	m_button_clear_filters = new wxButton(this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_button_clear_filters, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText21 = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum Value"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText21->Wrap(-1);
	bSizer41->Add(m_staticText21, 0, wxALL, 5);

	m_textCtrl_min_val = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer41->Add(m_textCtrl_min_val, 0, wxALL, 5);

	m_staticText211 = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText211->Wrap(-1);
	bSizer41->Add(m_staticText211, 0, wxALL, 5);

	m_textCtrl_max_val = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer41->Add(m_textCtrl_max_val, 0, wxALL, 5);


	bSizer3->Add(bSizer41, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText31 = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum Blocks"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText31->Wrap(-1);
	bSizer42->Add(m_staticText31, 0, wxALL, 5);

	m_textCtrl_min_blocks = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer42->Add(m_textCtrl_min_blocks, 0, wxALL, 5);

	m_staticText2111 = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2111->Wrap(-1);
	bSizer42->Add(m_staticText2111, 0, wxALL, 5);

	m_textCtrl_max_blocks = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer42->Add(m_textCtrl_max_blocks, 0, wxALL, 5);


	bSizer3->Add(bSizer42, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText33 = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum Memory Size"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText33->Wrap(-1);
	bSizer43->Add(m_staticText33, 0, wxALL, 5);

	m_textCtrl_min_mem = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer43->Add(m_textCtrl_min_mem, 0, wxALL, 5);

	m_staticText2112 = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2112->Wrap(-1);
	bSizer43->Add(m_staticText2112, 0, wxALL, 5);

	m_textCtrl_max_mem = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer43->Add(m_textCtrl_max_mem, 0, wxALL, 5);


	bSizer3->Add(bSizer43, 0, wxEXPAND, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame1::on_close));
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_open_db), this, m_menuItem_open_db->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_save_db), this, m_menuItem_save_db->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_update_db), this, m_menuItem_update_db->GetId());
	m_menu31->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_parse), this, m_menuItem_parse->GetId());
	m_menu31->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_test_func), this, m_menuItem_test_func->GetId());
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_help), this, m_menuItem_help->GetId());
	m_comboBox_table->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(MyFrame1::on_combobox_sel), NULL, this);
	m_button_apply_filters->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::on_button_click_apply_filters), NULL, this);
	m_button_clear_filters->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::on_button_click_clear_filters), NULL, this);

	m_open_dial = new MyDialog1(nullptr, wxID_ANY, "Open DB");
	m_open_dial->db_connected.bind(this, &MyFrame1::on_db_connected);

	m_textCtrl_min_val->SetValue("0");
	m_textCtrl_max_val->SetValue("0");
	m_textCtrl_min_blocks->SetValue("0");
	m_textCtrl_max_blocks->SetValue("0");
	m_textCtrl_min_mem->SetValue("0");
	m_textCtrl_max_mem->SetValue("0");

	std::cout << "DEBUG: Frame1 created!" << std::endl;
}

MyFrame1::~MyFrame1() {

	this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame1::on_close));
	m_comboBox_table->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(MyFrame1::on_combobox_sel), NULL, this);
	m_button_apply_filters->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::on_button_click_apply_filters), NULL, this);
	m_button_clear_filters->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::on_button_click_clear_filters), NULL, this);
}
