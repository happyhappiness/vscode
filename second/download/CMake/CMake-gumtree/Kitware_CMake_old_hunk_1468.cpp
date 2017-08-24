  // We want to display this on the right
  char version[cmCursesMainForm::MAX_WIDTH];
  char vertmp[128];
  sprintf(vertmp,"CMake Version %d.%d - %s", cmMakefile::GetMajorVersion(),
	  cmMakefile::GetMinorVersion(),cmMakefile::GetReleaseVersion());
  int sideSpace = (width-strlen(vertmp));
  for(i=0; i<sideSpace; i++) { version[i] = ' '; }
  sprintf(version+sideSpace, "%s", vertmp);
