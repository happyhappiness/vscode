    " -w/--write-out [format] What to output after completion",
    " -q                 If used as the first parameter disables .curlrc",
    NULL
  };
  for(i=0; helptext[i]; i++) {
    puts(helptext[i]);
#ifdef NETWARE
    if (i && ((i % 23) == 0))
      pressanykey();
#endif
  }
}

struct LongShort {
