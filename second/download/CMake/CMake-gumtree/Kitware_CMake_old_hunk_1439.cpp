    return false;
    }

  char* originalStr=0;

  char debugMessage[128];

  // <Enter> is used to change edit mode (like <Esc> in vi).
  while(1) 
    {
    sprintf(debugMessage, "String widget handling input, key: %d", key);
    cmCursesForm::LogMessage(debugMessage);
