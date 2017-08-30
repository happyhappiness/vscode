void cmCursesLongMessageForm::PrintKeys()
{
  int x,y;
  getmaxyx(stdscr, y, x);
  if ( x < cmCursesMainForm::MIN_WIDTH  || 
       y < cmCursesMainForm::MIN_HEIGHT )
    {
    return;
    }
  char firstLine[512];
  sprintf(firstLine,  "O)k");

  curses_move(y-2,0);
  printw(firstLine);
  pos_form_cursor(m_Form);
  
}