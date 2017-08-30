#include "memdebug.h"
#endif

char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  FILE *infp;
  char infp_fclose = 0;
  FILE *outfp;
  RETSIGTYPE (*sigint)();
#ifndef __EMX__
