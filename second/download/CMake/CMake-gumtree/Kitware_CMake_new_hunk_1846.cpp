void cmCursesMainForm::UpdateStatusBar()

{

  int x,y;

  getmaxyx(stdscr, y, x);

  if ( x < cmCursesMainForm::MIN_WIDTH  || 

       y < cmCursesMainForm::MIN_HEIGHT )

    {

    clear();

    curses_move(0,0);

    printw("Window is too small. A size of at least %dx%d is required.",

	   cmCursesMainForm::MIN_WIDTH, cmCursesMainForm::MIN_HEIGHT);

    touchwin(stdscr); 

    wrefresh(stdscr); 

    return;

    }



  FIELD* cur = current_field(m_Form);

  int index = field_index(cur);

  cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(

    m_Fields[index-2]));

  const char* curField = lbl->GetValue();



  // We want to display this on the right

  char help[128];

  const char* helpString;

  cmCacheManager::CacheEntry *entry = 

    cmCacheManager::GetInstance()->GetCacheEntry(curField);

  if (entry)

    {

    helpString = entry->m_HelpString.c_str();

    if (strlen(helpString) > 127)

      {

      sprintf(help,"%127s", helpString);

      }

    else

      {

      sprintf(help,"%s", helpString);

      }

    }

  else

    {

    sprintf(help," ");

    }





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



  int leftLen = width - helpLen;

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



  char version[cmCursesMainForm::MAX_WIDTH];

  char vertmp[128];

  sprintf(vertmp,"CMake Version %d.%d", cmMakefile::GetMajorVersion(),

	  cmMakefile::GetMinorVersion());

  int sideSpace = (width-strlen(vertmp));

  for(i=0; i<sideSpace; i++) { version[i] = ' '; }

  sprintf(version+sideSpace, "%s", vertmp);

  version[width] = '\0';



  curses_move(y-4,0);

  attron(A_STANDOUT);

  printw(bar);

  attroff(A_STANDOUT);  

  curses_move(y-3,0);

  printw(version);

  pos_form_cursor(m_Form);

}



void cmCursesMainForm::RunCMake(bool generateMakefiles)

{



  int x,y;

  getmaxyx(stdscr, y, x);



  clear();

  curses_move(1,1);

  printw("Running CMake, please wait.");

  touchwin(stdscr);

  refresh();

  endwin();

  // always save the current gui values to disk

  this->FillCacheManagerFromUI();

