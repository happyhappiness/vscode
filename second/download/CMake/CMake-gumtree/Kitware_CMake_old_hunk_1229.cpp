      }

    if ((!currentWidget || !widgetHandled) && !this->SearchMode)

      {

      // If the current widget does not want to handle input, 

      // we handle it.

      sprintf(debugMessage, "Main form handling input, key: %d", key);

      cmCursesForm::LogMessage(debugMessage);

