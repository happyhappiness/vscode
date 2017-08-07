  sprintf(version+sideSpace, "%s", vertmp);
  version[width] = '\0';

  char fmt_s[] = "%s";
  curses_move(y-4,0);
  attron(A_STANDOUT);
  printw(fmt_s, bar);
  attroff(A_STANDOUT);
  curses_move(y-3,0);
  printw(fmt_s, version);
  pos_form_cursor(this->Form);
}

