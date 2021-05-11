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
#include <wx/statbmp.h>

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

	MyDialog1* m_open_db_dialog;

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
	wxComboBox* m_combobox_table;
	wxStaticText* m_staticText11;
	wxCheckBox* m_checkbox_plot_market_val;
	wxCheckBox* m_checkbox_plot_dominance;
	wxCheckBox* m_checkbox_plot_transactions;
	wxCheckBox* m_checkbox_plot_outputs;
	wxButton* m_button_plot_create;
	wxStaticBitmap* m_bitmap_plot;
	wxStaticText* m_staticText2;
	wxStaticText* m_text_min_max_market_val;
	wxTextCtrl* m_textbox_min_market_val;
	wxStaticText* m_text_line_market_val;
	wxTextCtrl* m_textbox_max_market_val;
	wxStaticText* m_text_min_max_dominance;
	wxTextCtrl* m_textbox_min_dominance;
	wxStaticText* m_text_line_dominance;
	wxTextCtrl* m_textbox_max_dominance;
	wxStaticText* m_text_min_max_blocks;
	wxTextCtrl* m_textbox_min_blocks;
	wxStaticText* m_text_line_blocks;
	wxTextCtrl* m_textbox_max_blocks;
	wxStaticText* m_text_min_max_transactions;
	wxTextCtrl* m_textbox_min_transactions;
	wxStaticText* m_text_line_transactions;
	wxTextCtrl* m_textbox_max_transactions;
	wxStaticText* m_text_min_max_mem_transcations;
	wxTextCtrl* m_textbox_min_mem_transactions;
	wxStaticText* m_text_line_mem_transactions;
	wxTextCtrl* m_textbox_max_mem_transactions;
	wxStaticText* m_text_min_max_mem_tps;
	wxTextCtrl* m_textbox_min_mem_tps;
	wxStaticText* m_text_line_mem_tps;
	wxTextCtrl* m_textbox_max_mem_tps;
	wxButton* m_button_apply_filters;
	wxButton* m_button_clear_filters;

	virtual void on_close(wxCloseEvent& event);
	virtual void on_menu_sel_open_db(wxCommandEvent& event);
	virtual void on_menu_sel_save_db(wxCommandEvent& event);
	virtual void on_menu_sel_update_db(wxCommandEvent& event);
	virtual void on_menu_sel_parse(wxCommandEvent& event);
	virtual void on_menu_sel_help(wxCommandEvent& event);
	virtual void on_combobox_sel(wxCommandEvent& event);
	virtual void on_button_click_plot_create(wxCommandEvent& event) { event.Skip(); }
	virtual void on_button_click_apply_filters(wxCommandEvent& event);
	virtual void on_button_click_clear_filters(wxCommandEvent& event);

public:

	MyFrame1(const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(971, 550), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();
};

