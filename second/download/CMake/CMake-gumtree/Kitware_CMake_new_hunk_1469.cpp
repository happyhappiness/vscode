    CurrentForm = this;
    this->Render(1,1,x,y);
    }
   
  this->InitializeUI();
  this->Render(1, 1, x, y);
  
  return 0;
}

int cmCursesMainForm::Generate()
{
  m_CMakeInstance->Generate();
  
  int x,y;
  getmaxyx(stdscr, y, x);

  curses_clear();
  curses_move(1,1);
  touchwin(stdscr);
  refresh();
  endwin();
  std::cerr << "Generating, please wait...\n\r";

  // Get rid of previous errors
  m_Errors = std::vector<std::string>();

  // run the generate process
  int retVal = this->m_CMakeInstance->Generate();

  initscr(); /* Initialization */ 
  noecho(); /* Echo off */ 
  cbreak(); /* nl- or cr not needed */ 
  keypad(stdscr,TRUE); /* Use key symbols as 
			  KEY_DOWN*/ 

  if( retVal != 0 || !m_Errors.empty())
    {
    // see if there was an error
    if(cmSystemTools::GetErrorOccuredFlag())
      {
      m_OkToGenerate = false;
      }
    // reset error condition
    cmSystemTools::ResetErrorOccuredFlag();
    int x,y;
    getmaxyx(stdscr, y, x);
    cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
								"Errors which during last pass.");
    CurrentForm = msgs;
    msgs->Render(1,1,x,y);
    msgs->HandleInput();
    // If they typed the wrong source directory, we report
    // an error and exit
    if ( retVal == -2 )
      {
      return retVal;
      }
    CurrentForm = this;
    this->Render(1,1,x,y);
    }
  
  this->InitializeUI();
  this->Render(1, 1, x, y);
  
  return 0;
}

void cmCursesMainForm::AddError(const char* message, const char*)
{
  m_Errors.push_back(message);
