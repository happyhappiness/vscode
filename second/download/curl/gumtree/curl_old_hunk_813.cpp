#endif

#ifdef __SYMBIAN32__
#  define PRINT_LINES_PAUSE 16
#endif

void tool_help(void)
{
  int i;
  for(i = 0; helptext[i]; i++) {
    puts(helptext[i]);
#ifdef PRINT_LINES_PAUSE
    if(i && ((i % PRINT_LINES_PAUSE) == 0))
      tool_pressanykey();
#endif
  }
}
