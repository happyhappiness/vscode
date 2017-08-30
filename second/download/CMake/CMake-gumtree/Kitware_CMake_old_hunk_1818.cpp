    cw = reinterpret_cast<cmCursesWidget*>(field_userptr(currentField));
    }

  if (cw && cw->PrintKeys())
    {
    }
  else
    {
    char firstLine[512], secondLine[512], thirdLine[512];
    if (m_OkToGenerate)
      {
      sprintf(firstLine,  "Press [c] to configure     Press [g] to generate and exit");
      }
    else
      {
      sprintf(firstLine,  "Press [c] to configure");
      }
    if (m_AdvancedMode)
      {
