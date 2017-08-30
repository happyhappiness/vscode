#include "memdebug.h"

#endif



/* no perror? make an fprintf! */

#ifndef HAVE_PERROR

#  define perror(x) fprintf(stderr, "Error in: %s\n", x)

#endif



char *getpass_r(const char *prompt, char *buffer, size_t buflen)

{

  FILE *infp;

  FILE *outfp;

  RETSIGTYPE (*sigint)();

#ifndef __EMX__

