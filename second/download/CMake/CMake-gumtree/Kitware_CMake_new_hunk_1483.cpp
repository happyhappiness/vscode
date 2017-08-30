
  FORM* form = fm->GetForm();
  // 10 == enter
  if (!this->InEdit && ( key != 10 && key != KEY_ENTER ) )
    {
    return false;
    }

  this->OriginalString=0;
  this->Done = false;

  char debugMessage[128];

  // <Enter> is used to change edit mode (like <Esc> in vi).
  while(!this->Done)
    {
    sprintf(debugMessage, "String widget handling input, key: %d", key);
    cmCursesForm::LogMessage(debugMessage);
