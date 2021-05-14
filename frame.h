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
#include <wx/charts/wxcharts.h>

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
	std::map<std::string, CargoData<std::string>> m_caches_cargos_plot;
	
	uint32_t m_selected_row;

	void on_db_connected();
	void set_table_values_by_cargo(const CargoData<std::string>& cargo);
	void set_plot_values_by_cargo(const CargoData<std::string>& cargo);
	void set_plot_compare_values_by_cargo(const CargoData<std::string>& cargo, const CargoData<std::string>& cargo_compare);

protected:

	wxPanel* m_panel_plot;
	wxPanel* m_panel_plot_2;
	wxMenuBar* m_menubar4;
	wxMenu* m_menu2;
	wxMenu* m_menu31;
	wxMenu* m_menu3;
	wxGrid* m_grid_table;
	wxStaticText* m_staticText1;
	wxComboBox* m_combobox_table;
	wxStaticText* m_staticText11;
	wxComboBox* m_combobox_plot_coin;
	wxCheckBox* m_checkbox_compare_plot;
	wxComboBox* m_combobox_plot_coin_compare;
	wxStaticText* m_staticText21;
	wxStaticText* m_staticText2;
	wxStaticText* m_staticText266;
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
	wxStaticText* m_staticText22;

	wxChartsDoubleDataset::ptr m_data_set;
	wxChartsDoubleDataset::ptr m_data_set_2;
	wxChartsCategoricalData::ptr m_chart_data;
	wxLineChartCtrl* m_chart_line;
	wxChartsLegendCtrl* m_legend_line;

	wxChartsDoubleDataset::ptr m_data_set_3;
	wxChartsDoubleDataset::ptr m_data_set_4;
	wxChartsCategoricalData::ptr m_chart_data_2;
	wxLineChartCtrl* m_chart_line_2;
	wxChartsLegendCtrl* m_legend_line_2;

	virtual void on_close(wxCloseEvent& event);
	virtual void on_menu_sel_open_db(wxCommandEvent& event);
	virtual void on_menu_sel_save_db(wxCommandEvent& event);
	virtual void on_menu_sel_update_db(wxCommandEvent& event);
	virtual void on_menu_sel_delete_row(wxCommandEvent& event);
	virtual void on_menu_sel_add_row(wxCommandEvent& event);
	virtual void on_menu_sel_parse(wxCommandEvent& event);
	virtual void on_menu_sel_help(wxCommandEvent& event);
	virtual void on_combobox_sel(wxCommandEvent& event);
	virtual void on_grid_cell_change(wxGridEvent& event);
	virtual void on_grid_cell_select(wxGridEvent& event);
	virtual void on_button_click_apply_filters(wxCommandEvent& event);
	virtual void on_button_click_clear_filters(wxCommandEvent& event);
	virtual void on_combobox_coin_plot(wxCommandEvent& event);
	virtual void on_checkbox_compare_plot(wxCommandEvent& event);
	virtual void on_combobox_coin_plot_compare(wxCommandEvent& event);

public:

	MyFrame1(const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(971, 550), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();
};

