    {
    sprintf(debugMessage, "String widget handling input, key: %d", key);
    cmCursesForm::LogMessage(debugMessage);
    // If resize occured during edit, move out of edit mode
    if (!m_InEdit && ( key != 10 && key != KEY_ENTER ) )
      {
