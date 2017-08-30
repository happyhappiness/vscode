  // create a cmake object

  cmake make;

  // create the arguments for the cmake object

  std::vector<std::string> args;

  args.push_back(m_WhereCMake);

  if (m_WhereSource != "")

    {

    std::string arg;

    arg = m_WhereSource;

    args.push_back(arg);

    }

  // run the generate process

  if(make.Generate(args, generateMakefiles) != 0)

    {

    // TODO : error message here

    cmSystemTools::ResetErrorOccuredFlag();

    }



  m_Window = initscr(); /* Initialization */ 

  noecho(); /* Echo off */ 

  cbreak(); /* nl- or cr not needed */ 

  keypad(m_Window,TRUE); /* Use key symbols as 

			  KEY_DOWN*/ 

   

  this->InitializeUI(m_Window);

  this->Render(1, 1, x, y);

  

}



// copy from the list box to the cache manager

void cmCursesMainForm::FillCacheManagerFromUI()

{ 

