  // Now print both lines
  curses_move(y-5,0);
  attron(A_STANDOUT);
  printw(bar);
  attroff(A_STANDOUT);  
  curses_move(y-4,0);
  printw(version);
  pos_form_cursor(m_Form);
}

void cmCursesMainForm::UpdateProgress(const char *msg, float prog, void*)
{
  if ( prog < 0 )
    {
    std::cout << "-- " << msg << std::endl;
    }
}

int cmCursesMainForm::Configure()
{

  int xi,yi;
  getmaxyx(stdscr, yi, xi);

  curses_clear();
  curses_move(1,1);
  touchwin(stdscr);
  refresh();
  endwin();
  std::cerr << "Configuring, please wait...\n\r";
  this->m_CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);

  // always save the current gui values to disk
