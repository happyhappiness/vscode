  char firstLine[512];
  sprintf(firstLine,  "Press [e] to exit help");

  curses_move(y-2,0);
  printw(firstLine);
  pos_form_cursor(this->Form);

}