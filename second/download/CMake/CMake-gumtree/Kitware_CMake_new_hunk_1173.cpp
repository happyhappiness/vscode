// CMakeSetupDialog dialog
void updateProgress(const char *msg, float prog, void *cd)
{
  char* tmp = new char[strlen(msg) + 40];
  if (prog >= 0)
    {
    sprintf(tmp,"%s %i%%",msg,(int)(100*prog));
