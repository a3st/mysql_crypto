///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "dialog.h"
#include "global.h"

///////////////////////////////////////////////////////////////////////////

void MyDialog1::set_status(const bool connected) {

	if (connected) {

		m_statictext_status->SetLabelText("DB connected");
		m_statictext_status->SetForegroundColour(wxColour(4, 125, 37));
	} else {
		m_statictext_status->SetLabelText("DB not connected");
		m_statictext_status->SetForegroundColour(wxColour(213, 0, 0));
	}
}

void MyDialog1::on_button_click_con(wxCommandEvent& event)
{
	std::string fmt = std::string(m_textbox_address->GetValue().c_str().AsChar()) + ':' + std::string(m_textbox_port->GetValue().c_str().AsChar());
	sql::SQLString sql_addr = fmt;

	sql::SQLString login = m_textbox_login->GetValue().c_str().AsChar();
	sql::SQLString password = m_textbox_password->GetValue().c_str().AsChar();

	try {

		g_database_handler->connect(sql_addr, login, password);

		this->EndModal(1);
		::wxMessageBox("Соединение установлено с БД", "Информация");

		db_connected.call();
		this->set_status(true);
	}
	catch (std::exception& e) {
		::wxMessageBox(e.what(), "Ошибка");
	}
}

MyDialog1::MyDialog1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : 
	wxDialog(parent, id, title, pos, size, style) {

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);


	bSizer9->Add(0, 10, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText10 = new wxStaticText(this, wxID_ANY, wxT("Address:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText10->Wrap(-1);
	bSizer10->Add(m_staticText10, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_address = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
	bSizer10->Add(m_textbox_address, 0, wxALL, 5);

	m_staticText101 = new wxStaticText(this, wxID_ANY, wxT("Port:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText101->Wrap(-1);
	bSizer10->Add(m_staticText101, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_port = new wxTextCtrl(this, wxID_ANY, wxT("3306"), wxDefaultPosition, wxSize(50, -1), wxTE_CENTER);
	bSizer10->Add(m_textbox_port, 0, wxALL, 5);


	bSizer9->Add(bSizer10, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText102 = new wxStaticText(this, wxID_ANY, wxT("Login:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText102->Wrap(-1);
	bSizer101->Add(m_staticText102, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_login = new wxTextCtrl(this, wxID_ANY, wxT("root"), wxDefaultPosition, wxSize(80, -1), wxTE_CENTER);
	bSizer101->Add(m_textbox_login, 0, wxALL, 5);

	m_staticText1011 = new wxStaticText(this, wxID_ANY, wxT("Password:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1011->Wrap(-1);
	bSizer101->Add(m_staticText1011, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	m_textbox_password = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), wxTE_CENTER | wxTE_PASSWORD);
	bSizer101->Add(m_textbox_password, 0, wxALL, 5);


	bSizer9->Add(bSizer101, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxHORIZONTAL);

	m_button_con = new wxButton(this, wxID_ANY, wxT("Connect"), wxPoint(-1, -1), wxSize(-1, -1), 0);
	bSizer11->Add(m_button_con, 0, wxALL, 5);

	m_statictext_status = new wxStaticText(this, wxID_ANY, wxT("DB not connected"), wxDefaultPosition, wxDefaultSize, 0);
	m_statictext_status->Wrap(-1);
	m_statictext_status->SetForegroundColour(wxColour(213, 0, 0));

	bSizer11->Add(m_statictext_status, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer9->Add(bSizer11, 0, wxEXPAND | wxTOP, 5);


	this->SetSizer(bSizer9);
	this->Layout();

	this->Centre(wxBOTH);

	m_button_con->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyDialog1::on_button_click_con), NULL, this);
}

MyDialog1::~MyDialog1() {

	m_button_con->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyDialog1::on_button_click_con), NULL, this);
}
