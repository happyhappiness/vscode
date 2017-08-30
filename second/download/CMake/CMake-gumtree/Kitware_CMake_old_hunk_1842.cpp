    this->PrintKeys();

    int key = getch();



    currentField = current_field(m_Form);

    currentWidget = reinterpret_cast<cmCursesWidget*>(field_userptr(

      currentField));



    if (!currentWidget || !currentWidget->HandleInput(key, m_Form, stdscr))

      {

      sprintf(debugMessage, "Main form handling input, key: %d", key);

      cmCursesForm::LogMessage(debugMessage);

      // quit

