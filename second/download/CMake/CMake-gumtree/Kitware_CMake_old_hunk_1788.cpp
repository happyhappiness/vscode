      cmCursesForm::LogMessage(debugMessage);

      // quit

      if ( key == 'q' )

	{

	break;

	}

      // if not end of page, next field otherwise next page

      // each entry consists of fields: label, isnew, value

      // therefore, the label field for the prev. entry is index-5

      // and the label field for the next entry is index+1

      // (index always corresponds to the value field)

      else if ( key == KEY_DOWN || key == ctrl('n') )

	{

	FIELD* cur = current_field(m_Form);

	int index = field_index(cur);

	if ( index == 3*m_NumberOfVisibleEntries-1 )

	  {

	  continue;

	  }

	if (new_page(m_Fields[index+1]))

	  {

	  form_driver(m_Form, REQ_NEXT_PAGE);

	  }

	else

	  {

	  form_driver(m_Form, REQ_NEXT_FIELD);

	  }

	}

      // if not beginning of page, previous field, otherwise previous page

      // each entry consists of fields: label, isnew, value

      // therefore, the label field for the prev. entry is index-5

      // and the label field for the next entry is index+1

      // (index always corresponds to the value field)

      else if ( key == KEY_UP || key == ctrl('p') )

	{

	FIELD* cur = current_field(m_Form);

	int index = field_index(cur);

	if ( index == 2 )

	  {

	  continue;

	  }

	if ( new_page(m_Fields[index-2]) )

	  {

	  form_driver(m_Form, REQ_PREV_PAGE);

	  set_current_field(m_Form, m_Fields[index-3]);

	  }

	else

	  {

	  form_driver(m_Form, REQ_PREV_FIELD);

	  }

	}

      // pg down

      else if ( key == KEY_NPAGE || key == ctrl('d') )

	{

	form_driver(m_Form, REQ_NEXT_PAGE);

	}

      // pg up

      else if ( key == KEY_PPAGE || key == ctrl('u') )

	{

	form_driver(m_Form, REQ_PREV_PAGE);

	}

      // configure

      else if ( key == 'c' )

	{

	this->Configure();

	}

      // display help

      else if ( key == 'h' )

	{

	getmaxyx(stdscr, y, x);



	FIELD* cur = current_field(m_Form);

	int index = field_index(cur);

	cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(

	  m_Fields[index-2]));

	const char* curField = lbl->GetValue();

	const char* helpString=0;

	cmCacheManager::CacheIterator it = 

	  this->m_CMakeInstance->GetCacheManager()->GetCacheIterator(curField);

	if (!it.IsAtEnd())

	  {

	  helpString = it.GetProperty("HELPSTRING");

	  }

	if (helpString)

	  {

	  char* message = new char[strlen(curField)+strlen(helpString)

				  +strlen("Current option is: \n Help string for this option is: \n")+10];

	  sprintf(message,"Current option is: %s\nHelp string for this option is: %s\n", curField, helpString);

	  m_HelpMessage[1] = message;

	  delete[] message;

	  }

	else

	  {

	  m_HelpMessage[1] = "";

	  }



	cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_HelpMessage,

								    "Help.");

	CurrentForm = msgs;

	msgs->Render(1,1,x,y);

	msgs->HandleInput();

	CurrentForm = this;

	this->Render(1,1,x,y);

	}

      // display last errors

      else if ( key == 'l' )

	{

	getmaxyx(stdscr, y, x);

	cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,

								    "Errors occurred during the last pass.");

	CurrentForm = msgs;

	msgs->Render(1,1,x,y);

	msgs->HandleInput();

	CurrentForm = this;

	this->Render(1,1,x,y);

	}

      // switch advanced on/off

      else if ( key == 't' )

	{

	if (m_AdvancedMode)

	  {

	  m_AdvancedMode = false;

	  }

	else

	  {

	  m_AdvancedMode = true;

	  }

	getmaxyx(stdscr, y, x);

	this->RePost();

	this->Render(1, 1, x, y);

	}

      // generate and exit

      else if ( key == 'g' )

	{

	if ( m_OkToGenerate )

	  {

	  this->Generate();

	  break;

	  }

	}

      // delete cache entry

      else if ( key == 'd' )

	{

        m_OkToGenerate = false;

	FIELD* cur = current_field(m_Form);

	int index = field_index(cur);



	// make the next or prev. current field after deletion

	// each entry consists of fields: label, isnew, value

	// therefore, the label field for the prev. entry is index-5

	// and the label field for the next entry is index+1

	// (index always corresponds to the value field)

	FIELD* nextCur;

	if ( index == 2 )

	  {

	  nextCur=0;

	  }

	else if ( index == 3*m_NumberOfVisibleEntries-1 )

	  {

	  nextCur = m_Fields[index-5];

	  }

	else

	  {

	  nextCur = m_Fields[index+1];

	  }



	// Get the label widget

	// each entry consists of fields: label, isnew, value

	// therefore, the label field for the is index-2

	// (index always corresponds to the value field)

	cmCursesWidget* lbl = reinterpret_cast<cmCursesWidget*>(field_userptr(

	  m_Fields[index-2]));

	this->m_CMakeInstance->GetCacheManager()->RemoveCacheEntry(lbl->GetValue());



	std::string nextVal;

	if (nextCur)

	  {

	  nextVal = (reinterpret_cast<cmCursesWidget*>(field_userptr(nextCur))->GetValue());

	  }



	getmaxyx(stdscr, y, x);

	this->RemoveEntry(lbl->GetValue());

	this->RePost();

	this->Render(1, 1, x, y);



	if (nextCur)

	  {

	  // make the next or prev. current field after deletion

	  nextCur = 0;

	  std::vector<cmCursesCacheEntryComposite*>::iterator it;

	  for (it = m_Entries->begin(); it != m_Entries->end(); ++it)

	    {

	    if (nextVal == (*it)->m_Key)

	      {

	      nextCur = (*it)->m_Entry->m_Field;

	      }

	    }

	  

	  if (nextCur)

	    {

	    set_current_field(m_Form, nextCur);

	    }

	  }

	}

      }



    touchwin(stdscr); 
