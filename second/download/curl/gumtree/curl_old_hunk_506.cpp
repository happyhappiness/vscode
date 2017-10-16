    " -V/--version       Show version number and quit",

#ifdef USE_WATT32
    "    --wdebug        Turn on Watt-32 debugging",
#endif
    " -w/--write-out <format> What to output after completion",
    " -q                 If used as the first parameter disables .curlrc",
    NULL
  };
  for(i=0; helptext[i]; i++) {
    puts(helptext[i]);
#ifdef PRINT_LINES_PAUSE
