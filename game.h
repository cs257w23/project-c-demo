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
  // The state of the game. We use a vector instead of an array
  // because we don't know at compile time what the size of the
  // board is. We could also use templates (see the end of the book). 
  std::vector<std::vector<PlayerPiece>> board;

  PlayerPiece turn{PlayerPiece::Player1};
};

// A BoardGame is a GUI panel. This will be either
// a tic-tac-toe game or a Connect 4 game.
class BoardGame : public wxPanel {
  void OccupySpace(int row, int col);

  // Returns PlayerPiece::Empty if there is no winner.
  // Otherwise it returns the winning player.
  //
  // This is a pure virtual method. It must be implemented by
  // derived classes (tic-tac-toe or connect 4).
  virtual PlayerPiece Winner() const = 0;

  // Clear the board.
  void NewGame();

  // The cell panels. Each panel represents a game square.
  std::vector<std::vector<Cell*>> board_panels;

 protected:
  // The state of the game.
  GameState state;

  // The size of the board.
  int rows {0};
  int cols {0};

  // The parent of this panel. The parent of the board game
  // will be the window root panel.
  wxPanel* parent {0};

 public:
  // Constructor. Create a board game with rows, cols and attach
  // it to a parent panel.
  BoardGame(wxPanel* parent, int rows, int cols);

  // ALlow the Cell class access to private data and methods.
  friend class Cell;
};

class TicTacToeGame : public BoardGame {
  PlayerPiece Winner() const override;

 public:
  TicTacToeGame(wxPanel* parent) : BoardGame(parent, 3, 3) {}
};

class Connect4Game : public BoardGame {
  PlayerPiece Winner() const override;

 public:
  Connect4Game(wxPanel* parent) : BoardGame(parent, 6, 7) {}
};

// A GameFrame is the main visible GUI window.
// Everything that is GUI related and not part of the board game itself
// goes here. Currently that is:
//  - Menu.
//  - Winner dialog box.
//  - The main game panel.
class GameFrame : public wxFrame {
  wxMenuBar* menubar;
  wxMenu* file;

 protected:
  // The root panel. This is the parent of the board game.
  wxPanel* root_panel;

  // The two possible games.
  TicTacToeGame *tt_game {0};
  Connect4Game *c4_game {0};

  // Handle clicks for new tic-tac-toe games.
  void OnNewTTGame(wxCommandEvent& event);

  // Handle clicks for new Connect 4 games.
  void OnNewC4Game(wxCommandEvent& event);

 public:
  GameFrame(const wxString& title);

  void OnQuit(wxCommandEvent& event);
};

// This is the dialog box that is displayed when a game ends.
class WinnerDialog : public wxDialog {
 public:
  WinnerDialog(wxWindow* parent)
      : wxDialog(parent, wxID_ANY, wxString("Game over!")) {}
};

#endif
