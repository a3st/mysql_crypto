///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "frame.h"
#include "global.h"

///////////////////////////////////////////////////////////////////////////

void MyFrame1::on_db_connected()
{
	auto tables = g_database_handler->get_tables();
	
	std::vector<wxString> tables_;
	for (uint32_t i = 0; i < tables.size(); i++) {
		tables_.push_back(tables[i].c_str());
	}

	m_comboBox_table->Set(tables_);

	auto cargo_data = g_database_handler->get_table_data("currency");

	set_table_values_by_cargo(m_grid_table, cargo_data);
}

void MyFrame1::set_table_values_by_cargo(wxGrid* grid, const CargoData<std::string>& cargo)
{
	grid->DeleteRows(0, grid->GetNumberRows());
	grid->DeleteCols(0, grid->GetNumberCols());

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

void MyFrame1::on_menu_sel_open_db(wxCommandEvent& event)
{
	m_open_dial->ShowModal();
}

MyFrame1::MyFrame1(const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(nullptr, wxID_ANY, title, pos, size, style) {
	
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_menubar4 = new wxMenuBar(0);
	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem_open_db;
	m_menuItem_open_db = new wxMenuItem(m_menu2, wxID_ANY, wxString(wxT("Open DB")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuItem_open_db);

	wxMenuItem* m_menuItem_save_db;
	m_menuItem_save_db = new wxMenuItem(m_menu2, wxID_ANY, wxString(wxT("Save DB")), wxEmptyString, wxITEM_NORMAL);
	m_menu2->Append(m_menuItem_save_db);

	m_menubar4->Append(m_menu2, wxT("SQL"));

	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem(m_menu3, wxID_ANY, wxString(wxT("Bitcoin")), wxEmptyString, wxITEM_NORMAL);
	m_menu3->Append(m_menuItem5);

	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem(m_menu3, wxID_ANY, wxString(wxT("About")), wxEmptyString, wxITEM_NORMAL);
	m_menu3->Append(m_menuItem4);

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


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer4->Add(m_staticText2, 0, wxALL, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer4->Add(m_staticText3, 0, wxALL, 5);


	bSizer3->Add(bSizer4, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText21 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText21->Wrap(-1);
	bSizer41->Add(m_staticText21, 0, wxALL, 5);

	m_staticText31 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText31->Wrap(-1);
	bSizer41->Add(m_staticText31, 0, wxALL, 5);


	bSizer3->Add(bSizer41, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText22 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText22->Wrap(-1);
	bSizer42->Add(m_staticText22, 0, wxALL, 5);

	m_staticText32 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText32->Wrap(-1);
	bSizer42->Add(m_staticText32, 0, wxALL, 5);


	bSizer3->Add(bSizer42, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText23 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText23->Wrap(-1);
	bSizer43->Add(m_staticText23, 0, wxALL, 5);

	m_staticText33 = new wxStaticText(this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText33->Wrap(-1);
	bSizer43->Add(m_staticText33, 0, wxALL, 5);


	bSizer3->Add(bSizer43, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame1::on_menu_sel_open_db), this, m_menuItem_open_db->GetId());

	m_open_dial = new MyDialog1(nullptr, wxID_ANY, "Open DB");
	m_open_dial->db_connected.bind(this, &MyFrame1::on_db_connected);

	std::cout << "DEBUG: Frame1 created!" << std::endl;
}

MyFrame1::~MyFrame1() {
	
}
