{
  int x,y;
  getmaxyx(m_Window, y, x);
  if ( x < cmCursesMainForm::MIN_WIDTH  || 
       y < cmCursesMainForm::MIN_HEIGHT )
    {
    return;
    }
  char firstLine[512], secondLine[512];
  sprintf(firstLine,  "C)onfigure             G)enerate and Exit");
  sprintf(secondLine, "Q)uit                  H)elp");

  curses_move(y-2,0);
  printw(firstLine);
  curses_move(y-1,0);
  printw(secondLine);
  pos_form_cursor(m_Form);
  
}