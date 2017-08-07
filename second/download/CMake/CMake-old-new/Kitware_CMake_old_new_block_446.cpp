{
  int x,y;
  getmaxyx(stdscr, y, x);

  char bar[cmCursesMainForm::MAX_WIDTH];
  size_t size = strlen(this->Title.c_str());
  if ( size >= cmCursesMainForm::MAX_WIDTH )
    {
    size = cmCursesMainForm::MAX_WIDTH-1;
    }
  strncpy(bar, this->Title.c_str(), size);
  for(size_t i=size-1; i<cmCursesMainForm::MAX_WIDTH; i++) bar[i] = ' ';

  int width;
  if (x < cmCursesMainForm::MAX_WIDTH )
    {
    width = x;
    }
  else
    {
    width = cmCursesMainForm::MAX_WIDTH-1;
    }

  bar[width] = '\0';

  char version[cmCursesMainForm::MAX_WIDTH];
  char vertmp[128];
  sprintf(vertmp,"CMake Version %s", cmVersion::GetCMakeVersion());
  size_t sideSpace = (width-strlen(vertmp));
  for(size_t i=0; i<sideSpace; i++) { version[i] = ' '; }
  sprintf(version+sideSpace, "%s", vertmp);
  version[width] = '\0';

  curses_move(y-4,0);
  attron(A_STANDOUT);
  printw(bar);
  attroff(A_STANDOUT);
  curses_move(y-3,0);
  printw(version);
  pos_form_cursor(this->Form);
}