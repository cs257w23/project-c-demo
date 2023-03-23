#ifndef GAME_H
#define GAME_H

#include <wx/wx.h>

#include <vector>

class Cell;

enum class PlayerPiece {
  Empty,
  Player1,
  Player2,
};

struct GameState {
  // The state of the game.
  std::vector<std::vector<PlayerPiece>> board;

  PlayerPiece turn{PlayerPiece::Player1};
};

class BoardGame : public wxPanel {
  void OccupySpace(int row, int col);

  // Returns PlayerPiece::Empty if there is no winner.
  virtual PlayerPiece Winner() const = 0;
  void NewGame();

  // The cell panels. Each panel represents a game square.
  std::vector<std::vector<Cell*>> board_panels;

 protected:
  GameState state;

  int rows;
  int cols;
  wxPanel* parent;

 public:
  BoardGame(wxPanel* parent, int rows, int cols);

  friend class Cell;
};

class TicTacToeGame : public BoardGame {
  // Returns PlayerPiece::Empty if there is no winner.
  PlayerPiece Winner() const override;

 public:
  TicTacToeGame(wxPanel* parent) : BoardGame(parent, 3, 3) {}
};

class Connect4Game : public BoardGame {
  // Returns PlayerPiece::Empty if there is no winner.
  PlayerPiece Winner() const override;

 public:
  Connect4Game(wxPanel* parent) : BoardGame(parent, 6, 7) {}
};

class Game : public wxFrame {
  wxMenuBar* menubar;
  wxMenu* file;

 protected:
  // The main panel the board game object hangs off this panel.
  wxPanel* root_panel;

  TicTacToeGame *tt_game {0};
  Connect4Game *c4_game {0};

  void OnNewTTGame(wxCommandEvent& event);
  void OnNewC4Game(wxCommandEvent& event);

 public:
  Game(const wxString& title);

  void OnQuit(wxCommandEvent& event);
};

class WinnerDialog : public wxDialog {
 public:
  WinnerDialog(wxWindow* parent)
      : wxDialog(parent, wxID_ANY, wxString("Game over!")) {}
};

#endif
