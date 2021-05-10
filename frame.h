///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/grid.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/msgdlg.h>

#include "dialog.h"

#include "database_handler.h"
#include "data_miner.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
private:

	MyDialog1* m_open_dial;

	std::map<std::string, CargoData<std::string>> m_caches_cargos;

	void on_db_connected();

	void set_table_values_by_cargo(wxGrid* grid, const CargoData<std::string>& cargo);

protected:

	wxMenuBar* m_menubar4;
	wxMenu* m_menu2;
	wxMenu* m_menu31;
	wxMenu* m_menu3;
	wxGrid* m_grid_table;
	wxStaticText* m_staticText1;
	wxComboBox* m_comboBox_table;
	wxStaticText* m_staticText2;
	wxButton* m_button_apply_filters;
	wxButton* m_button_clear_filters;
	wxStaticText* m_staticText21;
	wxTextCtrl* m_textCtrl_min_val;
	wxStaticText* m_staticText211;
	wxTextCtrl* m_textCtrl_max_val;
	wxStaticText* m_staticText31;
	wxTextCtrl* m_textCtrl_min_blocks;
	wxStaticText* m_staticText2111;
	wxTextCtrl* m_textCtrl_max_blocks;
	wxStaticText* m_staticText33;
	wxTextCtrl* m_textCtrl_min_mem;
	wxStaticText* m_staticText2112;
	wxTextCtrl* m_textCtrl_max_mem;

	virtual void on_close(wxCloseEvent& event);
	virtual void on_menu_sel_open_db(wxCommandEvent& event);
	virtual void on_menu_sel_save_db(wxCommandEvent& event);
	virtual void on_menu_sel_update_db(wxCommandEvent& event);
	virtual void on_menu_sel_parse(wxCommandEvent& event);
	virtual void on_menu_sel_test_func(wxCommandEvent& event);
	virtual void on_menu_sel_help(wxCommandEvent& event);
	virtual void on_combobox_sel(wxCommandEvent& event);
	virtual void on_button_click_apply_filters(wxCommandEvent& event);
	virtual void on_button_click_clear_filters(wxCommandEvent& event);

public:

	MyFrame1(const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(902, 380), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();
};

