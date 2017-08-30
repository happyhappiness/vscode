  // create a cmake object

  cmake make;

  // create the arguments for the cmake object

  std::string whereCMake = cmSystemTools::GetProgramPath(m_Args[0].c_str());

  whereCMake += "/cmake";



  m_Args[0] = whereCMake;



  // Get rid of previous errors

  m_Errors = std::vector<std::string>();



  // run the generate process

  m_OkToGenerate = true;

  if(make.Generate(m_Args, generateMakefiles) != 0 || !m_Errors.empty())

    {

    m_OkToGenerate = false;

    cmSystemTools::ResetErrorOccuredFlag();

    int x,y;

    getmaxyx(stdscr, y, x);

    cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,

								"Errors which during last pass.");

    CurrentForm = msgs;

    msgs->Render(1,1,x,y);

    msgs->HandleInput();

    CurrentForm = this;

    this->Render(1,1,x,y);

    }



  initscr(); /* Initialization */ 

  noecho(); /* Echo off */ 

  cbreak(); /* nl- or cr not needed */ 

  keypad(stdscr,TRUE); /* Use key symbols as 

			  KEY_DOWN*/ 

   

  this->InitializeUI();

  this->Render(1, 1, x, y);

  

}



void cmCursesMainForm::AddError(const char* message, const char* title)

{

  m_Errors.push_back(message);

}



void cmCursesMainForm::RemoveEntry(const char* value)

{

  if (!value)

    {

    return;

    }



  std::vector<cmCursesCacheEntryComposite*>::iterator it;

  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)

    {

    const char* val = (*it)->GetValue();

    if (  val && !strcmp(value, val) )

      {

      m_Entries->erase(it);

      break;

      }

    }

}



// copy from the list box to the cache manager

void cmCursesMainForm::FillCacheManagerFromUI()

{ 

