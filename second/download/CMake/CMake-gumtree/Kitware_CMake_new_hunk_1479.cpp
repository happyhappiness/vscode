

  if (cw)

    {

    sprintf(firstLine, "Page %d of %d", cw->GetPage(), this->NumberOfPages);

    curses_move(0,65-strlen(firstLine)-1);

    printw(firstLine);

    }

//    }



  pos_form_cursor(this->Form);

  

}



