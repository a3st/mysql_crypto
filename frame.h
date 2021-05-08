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

	void on_db_connected();

	void set_table_values_by_cargo(wxGrid* grid, const CargoData<std::string>& cargo);

protected:
	wxMenuBar* m_menubar4;
	wxMenu* m_menu2;
	wxMenu* m_menu3;
	wxGrid* m_grid_table;
	wxStaticText* m_staticText1;
	wxComboBox* m_comboBox_table;
	wxStaticText* m_staticText2;
	wxStaticText* m_staticText3;
	wxStaticText* m_staticText21;
	wxStaticText* m_staticText31;
	wxStaticText* m_staticText22;
	wxStaticText* m_staticText32;
	wxStaticText* m_staticText23;
	wxStaticText* m_staticText33;

	virtual void on_menu_sel_open_db(wxCommandEvent& event);

public:

	MyFrame1(const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(938, 562), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MyFrame1();
};

