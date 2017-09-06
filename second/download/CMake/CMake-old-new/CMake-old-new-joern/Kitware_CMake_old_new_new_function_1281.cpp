void cmCursesMainForm::PrintKeys(int process /* = 0 */)
{
  int x,y;
  getmaxyx(stdscr, y, x);
  if ( x < cmCursesMainForm::MIN_WIDTH  || 
       x < this->InitialWidth               ||
       y < cmCursesMainForm::MIN_HEIGHT )
    {
    return;
    }

  // Give the current widget (if it exists), a chance to print keys
  cmCursesWidget* cw = 0;
  if (this->Form)
    {
    FIELD* currentField = current_field(this->Form);
    cw = reinterpret_cast<cmCursesWidget*>(field_userptr(currentField));
    }

  if (cw)
    {
    cw->PrintKeys();
    }
  
//    {
//    }
//  else
//    {
  char firstLine[512]="";
  char secondLine[512]="";
  char thirdLine[512]="";
  if (process)
    {
    sprintf(firstLine, 
            "                                                               ");  
    sprintf(secondLine, 
            "                                                               ");  
    sprintf(thirdLine, 
            "                                                               ");  
    }
  else
    {
    if (this->OkToGenerate)
      {
      sprintf(firstLine,  
              "Press [c] to configure     Press [g] to generate and exit");
      }
    else
      {
      sprintf(firstLine,  "Press [c] to configure                                   ");
      }
    if (this->AdvancedMode)
      {
      sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently On)");
      }
    else
      {
      sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently Off)");
      }
    
    sprintf(secondLine, 
            "Press [h] for help         Press [q] to quit without generating");
    }

  curses_move(y-4,0);
  char fmt[512] = "Press [enter] to edit option";
  if ( process )
    {
    strcpy(fmt, "                           ");
    }
  printw(fmt);
  curses_move(y-3,0);
  printw(firstLine);
  curses_move(y-2,0);
  printw(secondLine);
  curses_move(y-1,0);
  printw(thirdLine);

  if (cw)
    {
    sprintf(firstLine, "Page %d of %d", cw->GetPage(), this->NumberOfPages);
    curses_move(0,65-strlen(firstLine)-1);
    printw(firstLine);
    }
//    }

  pos_form_cursor(this->Form);
  
}