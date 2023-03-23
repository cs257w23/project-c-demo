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

class Game : public wxFrame {
  wxMenuBar* menubar;
  wxMenu* file;

 protected:
  // The main panel.
  wxPanel* root_panel;

 public:
  Game(const wxString& title);

  void OnQuit(wxCommandEvent& event);
};

class BoardGame : public Game {
  void OccupySpace(int row, int col);
  void OnNewGame(wxCommandEvent& event);

  // Returns PlayerPiece::Empty if there is no winner.
  virtual PlayerPiece Winner() const = 0;
  void NewGame();

  // The cell panels. Each panel represents a game square.
  std::vector<std::vector<Cell*>> board_panels;

 protected:
  GameState state;

  int rows;
  int cols;

 public:
  BoardGame(const wxString& title, int rows, int cols);
  virtual ~BoardGame() {}

  friend class Cell;
};

class WinnerDialog : public wxDialog {
 public:
  WinnerDialog(wxWindow* parent)
      : wxDialog(parent, wxID_ANY, wxString("Game over!")) {}
};

class TicTacToeGame : public BoardGame {
  // Returns PlayerPiece::Empty if there is no winner.
  PlayerPiece Winner() const override;

 public:
  TicTacToeGame(const wxString& title) : BoardGame(title, 3, 3) {}
};

#endif
