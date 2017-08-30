void cmCursesMainForm::UpdateStatusBar()
{
  int x,y;
  getmaxyx(m_Window, y, x);
  if ( x < cmCursesMainForm::MIN_WIDTH  || 
       y < cmCursesMainForm::MIN_HEIGHT )
    {
    curses_move(0,0);
    printw("Window is too small. A size of at least %dx%d is required.",
	   cmCursesMainForm::MIN_WIDTH, cmCursesMainForm::MIN_HEIGHT);
    touchwin(m_Window); 
    wrefresh(m_Window); 
    return;
    }

  FIELD* cur = current_field(m_Form);
  int index = field_index(cur);
  char* curField = field_buffer(m_Fields[index-2], 0);

  char version[128];
  sprintf(version,"(CMake Version %d.%d)", cmMakefile::GetMajorVersion(),
	  cmMakefile::GetMinorVersion());

  char bar[cmCursesMainForm::MAX_WIDTH];
  int i, curFieldLen = strlen(curField);
  int versionLen = strlen(version);
  int leftLen = cmCursesMainForm::IDEAL_WIDTH - versionLen;
  if (curFieldLen >= leftLen)
    {
    strncpy(bar, curField, leftLen);
    }
  else
    {
    strcpy(bar, curField);
    for(i=curFieldLen; i < leftLen; ++i) { bar[i] = ' '; }
    }
  strcpy(bar+leftLen, version);

  if ( x < cmCursesMainForm::MAX_WIDTH )
    {
    if (x > cmCursesMainForm::IDEAL_WIDTH )
      {
      for(i=cmCursesMainForm::IDEAL_WIDTH; i < x; i++)
	{
	bar[i] = ' ';
	}
      }
    bar[x] = '\0';
    }
  else
    {
    for(i=cmCursesMainForm::IDEAL_WIDTH; 
	i < cmCursesMainForm::MAX_WIDTH-1; i++)
      {
      bar[i] = ' ';
      }
    bar[cmCursesMainForm::MAX_WIDTH-1] = '\0';
    }

  curses_move(y-3,0);
  attron(A_STANDOUT);
  printw(bar);
  attroff(A_STANDOUT);  
  pos_form_cursor(m_Form);
}

void cmCursesMainForm::RunCMake(bool generateMakefiles)
{

  int x,y;
  getmaxyx(m_Window, y, x);
  
  endwin();
  // always save the current gui values to disk
  this->FillCacheManagerFromUI();
