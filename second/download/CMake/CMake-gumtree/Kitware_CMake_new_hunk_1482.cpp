          }

        }

      }

    if ( findex >= 3* this->NumberOfVisibleEntries-1 )

      {

      set_current_field(this->Form, this->Fields[2]);

      }

    else if (new_page(this->Fields[findex+1]))

      {

      form_driver(this->Form, REQ_NEXT_PAGE);

      }

    else

      {

      form_driver(this->Form, REQ_NEXT_FIELD);

      }

    /*

    char buffer[1024];

    sprintf(buffer, "Line: %d != %d / %d\n", findex, idx, this->NumberOfVisibleEntries);

    touchwin(stdscr); 

    refresh();

    this->UpdateStatusBar( buffer );

    usleep(100000);

    */

    cur = current_field(this->Form);

    findex = field_index(cur);

    if ( findex == start_index )

      {
