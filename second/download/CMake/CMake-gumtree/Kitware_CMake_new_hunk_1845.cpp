    return;
    }

  height -= 6;
  m_Height = height;

  if (m_AdvancedMode)
    {
    m_NumberOfVisibleEntries = m_Entries->size();
    }
  else
    {
    m_NumberOfVisibleEntries = 0;
    std::vector<cmCursesCacheEntryComposite*>::iterator it;
    for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
      {
      if (!m_AdvancedMode && cmCacheManager::GetInstance()->IsAdvanced(
	(*it)->GetValue()))
	{
	continue;
	}
      m_NumberOfVisibleEntries++;
      }
    }

  bool isNewPage;
  int i=0;
  std::vector<cmCursesCacheEntryComposite*>::iterator it;
  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)
    {
    if (!m_AdvancedMode && cmCacheManager::GetInstance()->IsAdvanced(
      (*it)->GetValue()))
      {
      continue;
      }
    int row = (i % height) + 1;  
    int page = (i / height) + 1;
    isNewPage = ( page > 1 ) && ( row == 1 );

    (*it)->m_Label->Move(left, top+row-1, isNewPage);
    (*it)->m_IsNewLabel->Move(left+32, top+row-1, false);
    (*it)->m_Entry->Move(left+33, top+row-1, false);
    i++;
    }

  m_Form = new_form(m_Fields);
  post_form(m_Form);
  this->UpdateStatusBar();
  this->PrintKeys();
  touchwin(stdscr); 
  refresh();
}

void cmCursesMainForm::PrintKeys()
{
  int x,y;
  getmaxyx(stdscr, y, x);
  if ( x < cmCursesMainForm::MIN_WIDTH  || 
       y < cmCursesMainForm::MIN_HEIGHT )
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
