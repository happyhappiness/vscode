    {
    return;
    }
  char firstLine[512], secondLine[512];
  if (m_OkToGenerate)
    {
    sprintf(firstLine,  "C)onfigure                 G)enerate and Exit            H)elp");
    }
  else
    {
    sprintf(firstLine,  "C)onfigure                                               H)elp");
    }
  if (m_AdvancedMode)
    {
    sprintf(secondLine, "Q)uit Without Generating   T)oggle Advanced Mode (On)");
    }
  else
    {
    sprintf(secondLine, "Q)uit Without Generating   T)oggle Advanced Mode (Off)");
    }

  curses_move(y-2,0);
  printw(firstLine);
  curses_move(y-1,0);
  printw(secondLine);
  pos_form_cursor(m_Form);
  
}
