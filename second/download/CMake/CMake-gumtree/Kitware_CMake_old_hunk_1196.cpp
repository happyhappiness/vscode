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
        set_current_field(m_Form, cur);
        }
      // display last errors
      else if ( key == 'l' )
        {
        getmaxyx(stdscr, y, x);
        cmCursesLongMessageForm* msgs = new cmCursesLongMessageForm(m_Errors,
                                                                    "Errors occurred during the last pass.");
        CurrentForm = msgs;
        msgs->Render(1,1,x,y);
