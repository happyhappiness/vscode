bool cmCursesStringWidget::PrintKeys()
{
  int x,y;
  getmaxyx(stdscr, y, x);
  if ( x < cmCursesMainForm::MIN_WIDTH  || 
       y < cmCursesMainForm::MIN_HEIGHT )
    {
    return false;
    }
  if (m_InEdit)
    {
    char firstLine[512];
    // Clean the toolbar
    for(int i=0; i<512; i++)
      {
      firstLine[i] = ' ';
      }
    firstLine[511] = '\0';
    curses_move(y-4,0);
    printw(firstLine);
    curses_move(y-3,0);
    printw(firstLine);
    curses_move(y-2,0);
    printw(firstLine);
    curses_move(y-1,0);
    printw(firstLine);

    sprintf(firstLine,  "Editing option, press [enter] to leave edit.");
    curses_move(y-3,0);
    printw(firstLine);
    return true;
    }
  else
    {
    return false;
    }
}