
#include "View.h"

///////////////////////////////////////////////////////////////////////////

MainMenu::MainMenu( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_button1 = new wxButton( this, wxID_ANY, wxT("New Game"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button1, 0, wxALL, 5 );

	m_button4 = new wxButton( this, wxID_ANY, wxT("Load Game"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button4, 0, wxALL, 5 );

	m_button2 = new wxButton( this, wxID_ANY, wxT("Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button2, 0, wxALL, 5 );

	m_button3 = new wxButton( this, wxID_ANY, wxT("Credits"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button3, 0, wxALL, 5 );

	m_button5 = new wxButton( this, wxID_ANY, wxT("Exit Game"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_button5, 0, wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );
}

MainMenu::~MainMenu()
{
}
