  sprintf(version+sideSpace, "%s", vertmp);
  version[width] = '\0';

  // Now print both lines
  curses_move(y-5,0);
  attron(A_STANDOUT);
  printw(bar);
  attroff(A_STANDOUT);  
  curses_move(y-4,0);
  printw(version);
  pos_form_cursor(m_Form);
}
