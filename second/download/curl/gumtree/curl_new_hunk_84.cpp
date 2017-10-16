    " -3/--sslv3         Use SSLv3 (SSL)",
    " -4/--ipv4          Resolve name to IPv4 address",
    " -6/--ipv6          Resolve name to IPv6 address",
    " -#/--progress-bar  Display transfer progress as a progress bar",
    NULL
  };
  for(i=0; helptext[i]; i++) {
    puts(helptext[i]);
#ifdef __NOVELL_LIBC__
    if (i && ((i % 23) == 0))
      pressanykey();
#endif
  }
}

struct LongShort {
  const char *letter;
  const char *lname;
  bool extraparam;
