#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "./brick_game/tetris/const.h"
#include "./brick_game/tetris/fsm.h"
#include "./brick_game/tetris/struct.h"
#include "./gui/cli/frontend.h"

int GameLoop(Parameters_t* parameters_);

void main() {
  //инициализация fsm
  FiniteStateMachine_t fsm_;
  InitializeFSM(&fsm_);

  //инициализация Parameters_t
  Board_t board_ = {0};
  Board_t game_board_ = {0};
  Board_t check_board_ = {0};
  Player_t current_player_ = {0};
  BlockType_t next_player_ = {0};
  PlayerState_t current_state_ = sStart;
  int current_level_ = 0;
  int current_score_ = 0;
  int current_speed_ = 500;
  int max_score_ = 0;

  Parameters_t parameters_ = {0};
  parameters_.fsm_ = &fsm_;
  parameters_.board_ = &board_;
  parameters_.game_board_ = &game_board_;
  parameters_.check_board_ = &check_board_;
  parameters_.current_player_ = &current_player_;
  parameters_.next_player_ = &next_player_;
  parameters_.current_state_ = &current_state_;
  parameters_.current_level_ = &current_level_;
  parameters_.current_score_ = &current_score_;
  parameters_.current_speed_ = &current_speed_;
  parameters_.max_score_ = &max_score_;

  //запуск и настройка ncurses
  srand(time(NULL));              //инициалзиация псевдослучайного ряда
  initscr();                      // инициализация дисплея
  keypad(stdscr, true);           // разрешить специальные символы
  noecho();                       // не показывать ввод
  curs_set(0);                    // спрятать курсор
  nodelay(stdscr, true);          // не ждет ответа пользователя
  GameLoop(&parameters_);
  endwin();                       // конец работы в интерфейсе
};

int GameLoop(Parameters_t* parameters_) {
//инициализация последнего нажатия
  LastKey_t last_key_ = {0, 0};
  bool hold = false;

  //разное
  int key = 0;
  UserAction_t user_action_ = 0;
  struct timeval last_update_time_, current_time_;
  gettimeofday(&last_update_time_, NULL);

  //игровой цикл
  while (*parameters_->current_state_ != sExitGame) {
    PrintActualScreen(parameters_);
    key = getch();
    if (key != ERR) {
      user_action_ = GetSignal(key, &hold, &last_key_);
      userInput(user_action_, hold, parameters_);
    };
    if (TimerAction(&last_update_time_, &current_time_,
                    *parameters_->current_speed_))
      userInput(Down, false, parameters_);
  };
  return 0;
};
