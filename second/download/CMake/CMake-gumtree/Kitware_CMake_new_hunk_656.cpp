  char firstLine[512];

  sprintf(firstLine,  "Press [e] to exit help");



  char fmt_s[] = "%s";

  curses_move(y-2,0);

  printw(fmt_s, firstLine);

  pos_form_cursor(this->Form);



}
