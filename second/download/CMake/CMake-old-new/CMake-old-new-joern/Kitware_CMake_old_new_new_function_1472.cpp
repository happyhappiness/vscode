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