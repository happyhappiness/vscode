  return haveData;
}

#if defined(_MSC_VER) && defined(_DEBUG)
# include <crtdbg.h>
# include <stdio.h>
# include <stdlib.h>
static int SystemToolsDebugReport(int, char* message, int*)
{
  fprintf(stderr, message);
