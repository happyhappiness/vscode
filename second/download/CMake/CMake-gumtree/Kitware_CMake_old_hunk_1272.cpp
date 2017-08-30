  char version[cmCursesMainForm::MAX_WIDTH];

  char vertmp[128];

  sprintf(vertmp,"CMake Version %s", cmVersion::GetCMakeVersion());

  int sideSpace = (width-strlen(vertmp));

  for(i=0; i<sideSpace; i++) { version[i] = ' '; }

  sprintf(version+sideSpace, "%s", vertmp);

  version[width] = '\0';

