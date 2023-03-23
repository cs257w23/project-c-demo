#include "game.h"

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    TicTacToeGame *game = new TicTacToeGame(wxT("Tic-tac-toe"));
    game->Show(true);

    return true;
}
