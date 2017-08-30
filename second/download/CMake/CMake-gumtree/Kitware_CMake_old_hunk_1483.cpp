

  FORM* form = fm->GetForm();

  // 10 == enter

  if (!m_InEdit && ( key != 10 && key != KEY_ENTER ) )

    {

    return false;

    }



  m_OriginalString=0;

  m_Done = false;



  char debugMessage[128];



  // <Enter> is used to change edit mode (like <Esc> in vi).

  while(!m_Done)

    {

    sprintf(debugMessage, "String widget handling input, key: %d", key);

    cmCursesForm::LogMessage(debugMessage);

