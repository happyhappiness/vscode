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

