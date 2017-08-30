    {

    sprintf(debugMessage, "String widget handling input, key: %d", key);

    cmCursesForm::LogMessage(debugMessage);



    fm->PrintKeys();



    getmaxyx(stdscr, y, x);

    // If window too small, handle 'q' only

    if ( x < cmCursesMainForm::MIN_WIDTH  || 

	 y < cmCursesMainForm::MIN_HEIGHT )

      {

      // quit

      if ( key == 'q' )

	{

	return false;

	}

      else

	{

	key=getch(); 

	continue;

	}

      }



    // If resize occured during edit, move out of edit mode

    if (!m_InEdit && ( key != 10 && key != KEY_ENTER ) )

      {

