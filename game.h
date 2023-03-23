#ifndef GAME_H
#define GAME_H

#include <wx/wx.h>

#include <array>

class Cell;

enum class PlayerPiece {
  Empty,
  Player1,
  Player2,
};

struct GameState {
  // The state of the game.
  std::array<std::array<PlayerPiece, 3>, 3> board;

  PlayerPiece turn{PlayerPiece::Player1};
};

class Game : public wxFrame {
  // The main panel.
  wxPanel* root_panel;

  // The cell panels. Each panel represents a game square.
  std::array<std::array<Cell*, 3>, 3> board_panels;

  GameState state;
  wxMenuBar* menubar;
  wxMenu* file;

  // Returns PlayerPiece::Empty if there is no winner.
  PlayerPiece Winner() const;
  void NewGame();

 public:
  Game(const wxString& title);

  void OccupySpace(int row, int col);
  void OnQuit(wxCommandEvent& event);
  void OnNewGame(wxCommandEvent& event);
};

class WinnerDialog : public wxDialog {
 public:
  WinnerDialog(wxWindow* parent)
      : wxDialog(parent, wxID_ANY, wxString("Game over!")) {}
};

#endif
