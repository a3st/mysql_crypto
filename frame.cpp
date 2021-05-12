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
	
	std::vector<wxString> tables_conv;
	for (uint32_t i = 0; i < tables.size(); i++) {
		tables_conv.push_back(tables[i].c_str());
	}
	m_combobox_table->Set(tables_conv);
	m_combobox_table->SetValue(tables_conv[0]);

	m_caches_cargos["currency"] = g_database_handler->get_table_data("currency");
	m_caches_cargos["mem_pool"] = g_database_handler->get_table_data("mem_pool");
	m_caches_cargos["stats"] = g_database_handler->get_table_data("stats");
	m_caches_cargos["daily"] = g_database_handler->get_table_data("daily");

	tables_conv.clear();
	for (uint32_t i = 1; i < m_caches_cargos["currency"].get_rows(); i++) {
		tables_conv.push_back(m_caches_cargos["currency"].get_data(i, 1).c_str());
	}
	m_combobox_plot_coin->Set(tables_conv);
	m_combobox_plot_coin->SetValue(tables_conv[0]);

	for (uint32_t i = 1; i < m_caches_cargos["currency"].get_rows(); i++) {

		const std::string coin_name = m_caches_cargos["currency"].get_data(i, 1);
		m_caches_cargos_plot[coin_name] = g_database_handler->get_coin_plot_data(coin_name);
	}

	this->set_plot_values_by_cargo(m_caches_cargos_plot[tables_conv[0].c_str().AsChar()]);
	this->set_table_values_by_cargo(m_caches_cargos["currency"]);
}

void MyFrame1::set_table_values_by_cargo(const CargoData<std::string>& cargo) {

	if (m_grid_table->GetNumberRows() > 0) {
		m_grid_table->DeleteRows(0, m_grid_table->GetNumberRows());
	}
	if (m_grid_table->GetNumberCols() > 0) {
		m_grid_table->DeleteCols(0, m_grid_table->GetNumberCols());
	}

	m_grid_table->InsertCols(0, cargo.get_cols());
	m_grid_table->InsertRows(0, cargo.get_rows() - 1);

	for (uint32_t i = 0; i < cargo.get_cols(); i++) {
		m_grid_table->SetColLabelValue(i, cargo.get_data(0, i));
	}

	for (uint32_t i = 1; i < cargo.get_rows(); i++) {
		for (uint32_t j = 0; j < cargo.get_cols(); j++) {
			m_grid_table->SetCellValue(i - 1, j, cargo.get_data(i, j));
		}
	}
}

void MyFrame1::set_plot_values_by_cargo(const CargoData<std::string>& cargo) {

	if (m_chart_data) {
		delete m_chart_line;
		delete m_legend_line;
		m_chart_data.~wxSharedPtr();
	}

	wxVector<wxString> labels;

	for (uint32_t i = 1; i < cargo.get_rows(); i++) {
		labels.push_back(cargo.get_data(i, 0));
	}

	m_chart_data = wxChartsCategoricalData::make_shared(labels);

	wxVector<wxDouble> points;
	for (uint32_t i = 1; i < cargo.get_rows(); i++) {
		points.push_back(std::stod(cargo.get_data(i, 1)));
	}

	m_data_set = new wxChartsDoubleDataset("market_value data_set", points);
	m_chart_data->AddDataset(m_data_set);

	// Create the line chart widget from the constructed data
	m_chart_line = new wxLineChartCtrl(m_panel_plot, wxID_ANY, m_chart_data,
		wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	// Create the legend widget
	wxChartsLegendData legend_data(m_chart_data->GetDatasets());
	m_legend_line = new wxChartsLegendCtrl(m_panel_plot, wxID_ANY, legend_data,
		wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	m_chart_line->SetSize(400, 200);
}

void MyFrame1::on_close(wxCloseEvent& event) {

	wxGetApp().Exit();
}

void MyFrame1::on_menu_sel_open_db(wxCommandEvent& event) {
	
	m_open_db_dialog->ShowModal();
}

void MyFrame1::on_menu_sel_save_db(wxCommandEvent& event) {
	
	try {

		g_database_handler->update_table_data("currency", m_caches_cargos["currency"]);
		g_database_handler->update_table_data("mem_pool", m_caches_cargos["mem_pool"]);
		g_database_handler->update_table_data("stats", m_caches_cargos["stats"]);
		g_database_handler->update_table_data("daily", m_caches_cargos["daily"]);
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "������");
	}
}

void MyFrame1::on_menu_sel_update_db(wxCommandEvent& event) {

	m_combobox_table->SetValue("currency");

	try {
		m_caches_cargos["currency"] = g_database_handler->get_table_data("currency");
		m_caches_cargos["mem_pool"] = g_database_handler->get_table_data("mem_pool");
		m_caches_cargos["stats"] = g_database_handler->get_table_data("stats");
		m_caches_cargos["daily"] = g_database_handler->get_table_data("daily");

		for (uint32_t i = 1; i < m_caches_cargos["currency"].get_rows(); i++) {

			const std::string coin_name = m_caches_cargos["currency"].get_data(i, 1);
			m_caches_cargos_plot[coin_name] = g_database_handler->get_coin_plot_data(coin_name);
		}

		this->set_plot_values_by_cargo(m_caches_cargos_plot[m_combobox_plot_coin->GetValue().c_str().AsChar()]);
		this->set_table_values_by_cargo(m_caches_cargos["currency"]);
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "������");
	}
}

void MyFrame1::on_menu_sel_parse(wxCommandEvent& event) {

	auto values = g_data_miner->parse();

	CargoData<std::string> currency_data(5);
	currency_data.new_line();
	currency_data.push_data("id");
	currency_data.push_data("coin_name");
	currency_data.push_data("market_value");
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

	CargoData<std::string> stats_data(7);
	stats_data.new_line();
	stats_data.push_data("id");
	stats_data.push_data("difficult");
	stats_data.push_data("next_difficult");
	stats_data.push_data("blockchain_size");
	stats_data.push_data("blocks");
	stats_data.push_data("transactions");
	stats_data.push_data("outputs");

	for (uint32_t i = 0; i < values.size(); i++) {

		stats_data.new_line();
		stats_data.push_data(std::to_string(coin_idx));
		stats_data.push_data(values[i]["difficulty"]);
		stats_data.push_data(values[i]["next_difficulty_estimate"]);
		stats_data.push_data(values[i]["blockchain_size"]);
		stats_data.push_data(values[i]["blocks"]);
		stats_data.push_data(values[i]["transactions"]);
		stats_data.push_data(values[i]["outputs"]);
		coin_idx++;
	}

	coin_idx = 0;

	CargoData<std::string> mem_pool_data(4);
	mem_pool_data.new_line();
	mem_pool_data.push_data("id");
	mem_pool_data.push_data("transactions");
	mem_pool_data.push_data("tps");
	mem_pool_data.push_data("mem_size");

	for (uint32_t i = 0; i < values.size(); i++) {

		mem_pool_data.new_line();
		mem_pool_data.push_data(std::to_string(coin_idx));
		mem_pool_data.push_data(values[i]["mempool_transactions"]);
		mem_pool_data.push_data(values[i]["mempool_tps"]);
		mem_pool_data.push_data(values[i]["mempool_size"]);
		coin_idx++;
	}

	coin_idx = 0;

	CargoData<std::string> daily_data(6);
	daily_data.new_line();
	daily_data.push_data("id");
	daily_data.push_data("date");
	daily_data.push_data("market_value");
	daily_data.push_data("dominance");
	daily_data.push_data("transactions");
	daily_data.push_data("outputs");

	time_t raw_time;
	struct tm* time_info;
	char buffer[80];

	::time(&raw_time);
	time_info = ::localtime(&raw_time);
	::strftime(buffer, 80, "%Y-%m-%d", time_info);

	for (uint32_t i = 0; i < values.size(); i++) {

		daily_data.new_line();
		daily_data.push_data(std::to_string(coin_idx));
		daily_data.push_data(buffer);
		daily_data.push_data(values[i]["market_price_usd"]);
		daily_data.push_data(values[i]["market_dominance_percentage"]);
		daily_data.push_data(values[i]["transactions"]);
		daily_data.push_data(values[i]["outputs"]);
		coin_idx++;
	}

	try {
		g_database_handler->insert_table_data("stats", stats_data);
		g_database_handler->insert_table_data("mem_pool", mem_pool_data);
		g_database_handler->insert_table_data("daily", daily_data);
		g_database_handler->insert_table_data("currency", currency_data);
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "������");
	}
}

void MyFrame1::on_menu_sel_help(wxCommandEvent& event) {

	::wxMessageBox(
		"������ ��������� �������� �������� ���������� � �������������.\n\
		��� ������ ��������� ��������� ���������� MySQL ������ � �� � ������������� ���������.\n\
		������� � �������� ��� ����� ����� � �����������, ��������� ����.\n\
		��� �������� ���������� ������������ ������ Blockchair.\n\
		\n\
		����� Dmitriy Lukovenko (github.com/A3st76)\n\
		MIT License.", "� ���������"
	);
}

void MyFrame1::on_combobox_sel(wxCommandEvent& event) {

	std::string cur = m_combobox_table->GetValue().c_str().AsChar();
	this->set_table_values_by_cargo(m_caches_cargos[cur]);
}

void MyFrame1::on_button_click_apply_filters(wxCommandEvent& event) {

	CargoData<std::string> cargo(6);
	cargo.new_line();
	cargo.push_data("currency.market_value");
	cargo.push_data("currency.dominance");
	cargo.push_data("stats.blocks");
	cargo.push_data("stats.transactions");
	cargo.push_data("mem_pool.transactions");
	cargo.push_data("mem_pool.tps");

	cargo.new_line();
	cargo.push_data(m_textbox_min_market_val->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_min_dominance->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_min_blocks->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_min_transactions->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_min_mem_transactions->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_min_mem_tps->GetValue().c_str().AsChar());

	cargo.new_line();
	cargo.push_data(m_textbox_max_market_val->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_max_dominance->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_max_blocks->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_max_transactions->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_max_mem_transactions->GetValue().c_str().AsChar());
	cargo.push_data(m_textbox_max_mem_tps->GetValue().c_str().AsChar());

	try {
		m_caches_cargos["filter"] = g_database_handler->get_filter_data(cargo);
		this->set_table_values_by_cargo(m_caches_cargos["filter"]);
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "������");
	}
}

void MyFrame1::on_button_click_clear_filters(wxCommandEvent& event) {

	std::string cur = m_combobox_table->GetValue().c_str().AsChar();
	if (!m_caches_cargos.empty()) {
		this->set_table_values_by_cargo(m_caches_cargos[cur]);
	}

	m_textbox_min_market_val->SetValue("0");
	m_textbox_min_dominance->SetValue("0");
	m_textbox_min_transactions->SetValue("0");
	m_textbox_min_blocks->SetValue("0");
	m_textbox_min_mem_transactions->SetValue("0");
	m_textbox_min_mem_tps->SetValue("0");
	m_textbox_max_market_val->SetValue("0");
	m_textbox_max_dominance->SetValue("0");
	m_textbox_max_transactions->SetValue("0");
	m_textbox_max_blocks->SetValue("0");
	m_textbox_max_mem_transactions->SetValue("0");
	m_textbox_max_mem_tps->SetValue("0");
}

void MyFrame1::on_combobox_coin_plot(wxCommandEvent& event) {

	std::string cur = m_combobox_plot_coin->GetValue().c_str().AsChar();
	this->set_plot_values_by_cargo(m_caches_cargos_plot[cur]);
}

MyFrame1::MyFrame1(const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(nullptr, wxID_ANY, title, pos, size, style) {
	
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	m_menubar4 = new wxMenuBar(0);
	m_menu2 = new wxMenu();
	wxMenuItem* m_menuitem_open_db;
	m_menuitem_open_db = new wxMenuItem(m_menu2, wxID_ANY, wxString(wxT("Open")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuitem_open_db);

	wxMenuItem* m_menuitem_save_db;
	m_menuitem_save_db = new wxMenuItem(m_menu2, wxID_ANY, wxString(wxT("Save")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuitem_save_db);

	wxMenuItem* m_menuitem_update_db;
	m_menuitem_update_db = new wxMenuItem(m_menu2, wxID_ANY, wxString(wxT("Update")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuitem_update_db);

	m_menubar4->Append(m_menu2, wxT("Database"));

	m_menu31 = new wxMenu();
	wxMenuItem* m_menuitem_parse;
	m_menuitem_parse = new wxMenuItem(m_menu31, wxID_ANY, wxString(wxT("Parse from Blockchair.API")), wxEmptyString, wxITEM_NORMAL);
	m_menu31->Append(m_menuitem_parse);

	m_menubar4->Append(m_menu31, wxT("Tools"));

	m_menu3 = new wxMenu();
	wxMenuItem* m_menuitem_help;
	m_menuitem_help = new wxMenuItem(m_menu3, wxID_ANY, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
	m_menu3->Append(m_menuitem_help);

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
	m_grid_table->SetGridLineColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));
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
	m_grid_table->SetLabelBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
	m_grid_table->SetLabelFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	m_grid_table->SetLabelTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_CAPTIONTEXT));

	// Cell Defaults
	m_grid_table->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	m_grid_table->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	bSizer8->Add(m_grid_table, 0, wxALL | wxEXPAND, 5);


	bSizer1->Add(bSizer8, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Current table"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer38->Add(m_staticText1, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_combobox_table = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	bSizer38->Add(m_combobox_table, 0, wxALL, 5);


	bSizer12->Add(bSizer38, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer(wxVERTICAL);

	m_staticText11 = new wxStaticText(this, wxID_ANY, wxT("Market Value Plot"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText11->Wrap(-1);
	bSizer39->Add(m_staticText11, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText21 = new wxStaticText(this, wxID_ANY, wxT("Coin"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText21->Wrap(-1);
	bSizer40->Add(m_staticText21, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_combobox_plot_coin = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	bSizer40->Add(m_combobox_plot_coin, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	bSizer39->Add(bSizer40, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer(wxVERTICAL);

	m_panel_plot = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 200), wxTAB_TRAVERSAL);

	wxVector<wxString> labels;
	m_chart_data = wxChartsCategoricalData::make_shared(labels);

	// Create the line chart widget from the constructed data
	m_chart_line = new wxLineChartCtrl(m_panel_plot, wxID_ANY, m_chart_data,
		wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	// Create the legend widget
	wxChartsLegendData legend_data(m_chart_data->GetDatasets());
	m_legend_line = new wxChartsLegendCtrl(m_panel_plot, wxID_ANY, legend_data,
		wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	m_chart_line->SetSize(400, 200);

	bSizer42->Add(m_panel_plot, 1, wxEXPAND | wxALL, 5);


	bSizer39->Add(bSizer42, 0, wxEXPAND, 5);


	bSizer12->Add(bSizer39, 0, wxEXPAND, 5);


	bSizer2->Add(bSizer12, 1, wxEXPAND, 5);


	bSizer2->Add(100, 0, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer(wxVERTICAL);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Filters"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	m_staticText2->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

	bSizer14->Add(m_staticText2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);


	bSizer13->Add(bSizer14, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer(wxHORIZONTAL);

	m_text_min_max_market_val = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum Market Value ($)"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_min_max_market_val->Wrap(-1);
	bSizer23->Add(m_text_min_max_market_val, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_min_market_val = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer23->Add(m_textbox_min_market_val, 0, wxALL, 5);

	m_text_line_market_val = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_line_market_val->Wrap(-1);
	bSizer23->Add(m_text_line_market_val, 0, wxALIGN_CENTER | wxALL, 5);

	m_textbox_max_market_val = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer23->Add(m_textbox_max_market_val, 0, wxALL, 5);


	bSizer16->Add(bSizer23, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer231;
	bSizer231 = new wxBoxSizer(wxHORIZONTAL);

	m_text_min_max_dominance = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum Dominance (%)"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_min_max_dominance->Wrap(-1);
	bSizer231->Add(m_text_min_max_dominance, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_min_dominance = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer231->Add(m_textbox_min_dominance, 0, wxALL, 5);

	m_text_line_dominance = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_line_dominance->Wrap(-1);
	bSizer231->Add(m_text_line_dominance, 0, wxALIGN_CENTER | wxALL, 5);

	m_textbox_max_dominance = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer231->Add(m_textbox_max_dominance, 0, wxALL, 5);


	bSizer16->Add(bSizer231, 0, wxEXPAND, 5);


	bSizer13->Add(bSizer16, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer161;
	bSizer161 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer232;
	bSizer232 = new wxBoxSizer(wxHORIZONTAL);

	m_text_min_max_blocks = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum Blocks"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_min_max_blocks->Wrap(-1);
	bSizer232->Add(m_text_min_max_blocks, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_min_blocks = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer232->Add(m_textbox_min_blocks, 0, wxALL, 5);

	m_text_line_blocks = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_line_blocks->Wrap(-1);
	bSizer232->Add(m_text_line_blocks, 0, wxALIGN_CENTER | wxALL, 5);

	m_textbox_max_blocks = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer232->Add(m_textbox_max_blocks, 0, wxALL, 5);


	bSizer161->Add(bSizer232, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer233;
	bSizer233 = new wxBoxSizer(wxHORIZONTAL);

	m_text_min_max_transactions = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum Transactions"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_min_max_transactions->Wrap(-1);
	bSizer233->Add(m_text_min_max_transactions, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_min_transactions = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer233->Add(m_textbox_min_transactions, 0, wxALL, 5);

	m_text_line_transactions = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_line_transactions->Wrap(-1);
	bSizer233->Add(m_text_line_transactions, 0, wxALIGN_CENTER | wxALL, 5);

	m_textbox_max_transactions = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer233->Add(m_textbox_max_transactions, 0, wxALL, 5);


	bSizer161->Add(bSizer233, 0, wxEXPAND, 5);


	bSizer13->Add(bSizer161, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer1611;
	bSizer1611 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer2321;
	bSizer2321 = new wxBoxSizer(wxHORIZONTAL);

	m_text_min_max_mem_transcations = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum Transactions"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_min_max_mem_transcations->Wrap(-1);
	bSizer2321->Add(m_text_min_max_mem_transcations, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_min_mem_transactions = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer2321->Add(m_textbox_min_mem_transactions, 0, wxALL, 5);

	m_text_line_mem_transactions = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_line_mem_transactions->Wrap(-1);
	bSizer2321->Add(m_text_line_mem_transactions, 0, wxALIGN_CENTER | wxALL, 5);

	m_textbox_max_mem_transactions = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer2321->Add(m_textbox_max_mem_transactions, 0, wxALL, 5);


	bSizer1611->Add(bSizer2321, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer23211;
	bSizer23211 = new wxBoxSizer(wxHORIZONTAL);

	m_text_min_max_mem_tps = new wxStaticText(this, wxID_ANY, wxT("Minimum - Maximum TPS"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_min_max_mem_tps->Wrap(-1);
	bSizer23211->Add(m_text_min_max_mem_tps, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_min_mem_tps = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer23211->Add(m_textbox_min_mem_tps, 0, wxALL, 5);

	m_text_line_mem_tps = new wxStaticText(this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0);
	m_text_line_mem_tps->Wrap(-1);
	bSizer23211->Add(m_text_line_mem_tps, 0, wxALIGN_CENTER | wxALL, 5);

	m_textbox_max_mem_tps = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer23211->Add(m_textbox_max_mem_tps, 0, wxALL, 5);


	bSizer1611->Add(bSizer23211, 0, wxEXPAND, 5);


	bSizer13->Add(bSizer1611, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer(wxHORIZONTAL);

	m_button_apply_filters = new wxButton(this, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer15->Add(m_button_apply_filters, 0, wxALL, 5);

	m_button_clear_filters = new wxButton(this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer15->Add(m_button_clear_filters, 0, wxALL, 5);


	bSizer13->Add(bSizer15, 1, wxEXPAND, 5);


	bSizer2->Add(bSizer13, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame1::on_close));
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_open_db), this, m_menuitem_open_db->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_save_db), this, m_menuitem_save_db->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_update_db), this, m_menuitem_update_db->GetId());
	m_menu31->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_parse), this, m_menuitem_parse->GetId());
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_help), this, m_menuitem_help->GetId());
	m_combobox_table->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(MyFrame1::on_combobox_sel), NULL, this);
	m_button_apply_filters->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::on_button_click_apply_filters), NULL, this);
	m_button_clear_filters->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::on_button_click_clear_filters), NULL, this);
	m_combobox_plot_coin->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(MyFrame1::on_combobox_coin_plot), NULL, this);

	m_open_db_dialog = new MyDialog1(nullptr, wxID_ANY, "DB Connection Settings");
	m_open_db_dialog->db_connected.bind(this, &MyFrame1::on_db_connected);

	m_textbox_min_market_val->SetValue("0");
	m_textbox_min_dominance->SetValue("0");
	m_textbox_min_transactions->SetValue("0");
	m_textbox_min_blocks->SetValue("0");
	m_textbox_min_mem_transactions->SetValue("0");
	m_textbox_min_mem_tps->SetValue("0");
	m_textbox_max_market_val->SetValue("0");
	m_textbox_max_dominance->SetValue("0");
	m_textbox_max_transactions->SetValue("0");
	m_textbox_max_blocks->SetValue("0");
	m_textbox_max_mem_transactions->SetValue("0");
	m_textbox_max_mem_tps->SetValue("0");
}

MyFrame1::~MyFrame1() {

	this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame1::on_close));
	m_combobox_table->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(MyFrame1::on_combobox_sel), NULL, this);
	m_button_apply_filters->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::on_button_click_apply_filters), NULL, this);
	m_button_clear_filters->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::on_button_click_clear_filters), NULL, this);
	m_combobox_plot_coin->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(MyFrame1::on_combobox_coin_plot), NULL, this);
}