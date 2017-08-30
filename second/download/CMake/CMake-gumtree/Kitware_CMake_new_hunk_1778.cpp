  // Now print both lines

  curses_move(y-5,0);

  attron(A_STANDOUT);

  printw("%s", bar);

  attroff(A_STANDOUT);  

  curses_move(y-4,0);

  printw(version);

  pos_form_cursor(m_Form);

}



void cmCursesMainForm::UpdateProgressOld(const char *msg, float prog, void*)

{

  if ( prog < 0 )

    {

    std::cout << "-- " << msg << std::endl;

    }

}



void cmCursesMainForm::UpdateProgress(const char *msg, float prog, void* vp)

{

  cmCursesMainForm* cm = static_cast<cmCursesMainForm*>(vp);

  if ( !cm )

    {

    return;

    }

  char tmp[1024];

  const char *cmsg = tmp;

  if ( prog >= 0 )

    {

    sprintf(tmp, "%s %i%%",msg,(int)(100*prog));

    }

  else

    {

    cmsg = msg;

    }

  cm->UpdateStatusBar(cmsg);

  cm->PrintKeys(1);

  curses_move(1,1);

  touchwin(stdscr); 

  refresh();

}



int cmCursesMainForm::Configure()

{



  int xi,yi;

  getmaxyx(stdscr, yi, xi);



  curses_move(1,1);

  this->UpdateStatusBar("Configuring, please wait...");

  this->PrintKeys(1);

  touchwin(stdscr); 

  refresh();

  this->m_CMakeInstance->SetProgressCallback(cmCursesMainForm::UpdateProgress, this);



  // always save the current gui values to disk

