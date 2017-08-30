      sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently Off)");
      }
    
    sprintf(secondLine, 
            "Press [h] for help         Press [q] to quit without generating");
    }

  curses_move(y-4,0);
  char *fmt = "Press [enter] to edit option";
  if ( process )
    {
    fmt = "                           ";
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
    sprintf(firstLine, "Page %d of %d", cw->GetPage(), m_NumberOfPages);
    curses_move(0,65-strlen(firstLine)-1);
    printw(firstLine);
    }
//    }

  pos_form_cursor(m_Form);
