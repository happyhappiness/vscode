          }
        }
      }
    if ( findex >= 3* m_NumberOfVisibleEntries-1 )
      {
      set_current_field(m_Form, m_Fields[2]);
      }
    else if (new_page(m_Fields[findex+1]))
      {
      form_driver(m_Form, REQ_NEXT_PAGE);
      }
    else
      {
      form_driver(m_Form, REQ_NEXT_FIELD);
      }
    /*
    char buffer[1024];
    sprintf(buffer, "Line: %d != %d / %d\n", findex, idx, m_NumberOfVisibleEntries);
    touchwin(stdscr); 
    refresh();
    this->UpdateStatusBar( buffer );
    usleep(100000);
    */
    cur = current_field(m_Form);
    findex = field_index(cur);
    if ( findex == start_index )
      {