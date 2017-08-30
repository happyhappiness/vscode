  if (cw)

    {

    sprintf(firstLine, "Page %d of %d", cw->GetPage(), this->NumberOfPages);

    curses_move(0,65-static_cast<unsigned int>(strlen(firstLine))-1);

    printw(firstLine);

    }

//    }

