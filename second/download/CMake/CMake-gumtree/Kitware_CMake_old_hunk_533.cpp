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
    curses_move(0,65-static_cast<unsigned int>(strlen(firstLine))-1);
    printw(firstLine);
    }
//    }

