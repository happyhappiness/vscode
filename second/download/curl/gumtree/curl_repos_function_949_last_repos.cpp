void tool_help(void)
{
  int i;
  puts("Usage: curl [options...] <url>");
  for(i = 0; helptext[i].opt; i++) {
    printf(" %-19s %s\n", helptext[i].opt, helptext[i].desc);
#ifdef PRINT_LINES_PAUSE
    if(i && ((i % PRINT_LINES_PAUSE) == 0))
      tool_pressanykey();
#endif
  }
}