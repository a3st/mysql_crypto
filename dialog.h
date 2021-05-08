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
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/msgdlg.h>

#include "delegate.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog1
///////////////////////////////////////////////////////////////////////////////
class MyDialog1 : public wxDialog
{
private:

protected:

	wxStaticText* m_staticText10;
	wxTextCtrl* m_textCtrl_address;
	wxStaticText* m_staticText101;
	wxTextCtrl* m_textCtrl_port;
	wxButton* m_button_con;

	virtual void on_button_click_con(wxCommandEvent& event);

public:

	MyDialog1(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(291, 127), long style = wxDEFAULT_DIALOG_STYLE);
	~MyDialog1();

	Delegate db_connected;

};