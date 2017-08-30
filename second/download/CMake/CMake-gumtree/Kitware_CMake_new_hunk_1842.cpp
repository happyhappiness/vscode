    this->PrintKeys();

    int key = getch();



    getmaxyx(stdscr, y, x);

    // If window too small, handle 'q' only

    if ( x < cmCursesMainForm::MIN_WIDTH  || 

	 y < cmCursesMainForm::MIN_HEIGHT )

      {

      // quit

      if ( key == 'q' )

	{

	break;

	}

      else

	{

	continue;

	}

      }



    currentField = current_field(m_Form);

    currentWidget = reinterpret_cast<cmCursesWidget*>(field_userptr(

      currentField));



    // Ask the current widget if it wants to handle input

    if (!currentWidget || !currentWidget->HandleInput(key, this, stdscr))

      {

      // If the current widget does not want to handle input, 

      // we handle it.

      sprintf(debugMessage, "Main form handling input, key: %d", key);

      cmCursesForm::LogMessage(debugMessage);

      // quit

