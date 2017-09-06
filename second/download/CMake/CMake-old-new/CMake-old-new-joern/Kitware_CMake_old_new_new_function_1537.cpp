void cmCursesMainForm::UpdateStatusBar()
{
  int x,y;
  getmaxyx(stdscr, y, x);
  // If window size is too small, display error and return
  if ( x < cmCursesMainForm::MIN_WIDTH  || 
       x < m_InitialWidth               ||
       y < cmCursesMainForm::MIN_HEIGHT )
    {
    curses_clear();
    curses_move(0,0);
    char fmt[] = "Window is too small. A size of at least %dx%d is required.";
    printw(fmt,
	   (cmCursesMainForm::MIN_WIDTH < m_InitialWidth ?
	    m_InitialWidth : cmCursesMainForm::MIN_WIDTH), 
	   cmCursesMainForm::MIN_HEIGHT);
    touchwin(stdscr); 
    wrefresh(stdscr); 
    return;
    }

  // Get the key of the current entry
  FIELD* cur = current_field(m_Form);
  int index = field_index(cur);
  cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(
    m_Fields[index-2]));
  const char* curField = lbl->GetValue();

  // Get the help string of the current entry
  // and add it to the help string
  char help[128];
  const char* helpString;
  cmCacheManager::CacheEntry *entry = 
    this->m_CMakeInstance->GetCacheManager()->GetCacheEntry(curField);
  if (entry)
    {
    helpString = entry->m_HelpString.c_str();
    strncpy(help, helpString, 127);
    help[127] = '\0';
    }
  else
    {
    sprintf(help," ");
    }


  // Join the key, help string and pad with spaces
  // (or truncate) as necessary
  char bar[cmCursesMainForm::MAX_WIDTH];
  int i, curFieldLen = strlen(curField);
  int helpLen = strlen(help);

  int width;
  if (x < cmCursesMainForm::MAX_WIDTH )
    {
    width = x;
    }
  else
    {
    width = cmCursesMainForm::MAX_WIDTH;
    }

  if (curFieldLen >= width)
    {
    strncpy(bar, curField, width);
    }
  else
    {
    strcpy(bar, curField);
    bar[curFieldLen] = ':';
    bar[curFieldLen+1] = ' ';
    if (curFieldLen + helpLen + 2 >= width)
      {
      strncpy(bar+curFieldLen+2, help, width
	- curFieldLen - 2);
      }
    else
      {
      strcpy(bar+curFieldLen+2, help);
      for(i=curFieldLen+helpLen+2; i < width; ++i) 
	{ 
	bar[i] = ' '; 
	}
      }
    }

  bar[width] = '\0';

  // Display CMake version info on the next line
  // We want to display this on the right
  char version[cmCursesMainForm::MAX_WIDTH];
  char vertmp[128];
  sprintf(vertmp,"CMake Version %d.%d - %s", cmake::GetMajorVersion(),
	  cmake::GetMinorVersion(),cmake::GetReleaseVersion());
  int sideSpace = (width-strlen(vertmp));
  for(i=0; i<sideSpace; i++) { version[i] = ' '; }
  sprintf(version+sideSpace, "%s", vertmp);
  version[width] = '\0';

  // Now print both lines
  curses_move(y-5,0);
  attron(A_STANDOUT);
  printw(bar);
  attroff(A_STANDOUT);  
  curses_move(y-4,0);
  printw(version);
  pos_form_cursor(m_Form);
}