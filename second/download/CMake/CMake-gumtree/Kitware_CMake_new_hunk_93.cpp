                                         FILE* stream, int color);

#endif



void kwsysTerminal_cfprintf(int color, FILE* stream, const char* format, ...)

{

  /* Setup the stream with the given color if possible.  */

