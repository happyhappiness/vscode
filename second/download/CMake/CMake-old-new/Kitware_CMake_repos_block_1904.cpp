{
  (void)argc;
  (void)argv;
  kwsysTerminal_cfprintf(kwsysTerminal_Color_ForegroundYellow |
                           kwsysTerminal_Color_BackgroundBlue |
                           kwsysTerminal_Color_AssumeTTY,
                         stdout, "Hello %s!", "World");
  fprintf(stdout, "\n");
  return 0;
}