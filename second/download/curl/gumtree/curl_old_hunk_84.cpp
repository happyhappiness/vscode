    " -3/--sslv3         Use SSLv3 (SSL)",
    " -4/--ipv4          Resolve name to IPv4 address",
    " -6/--ipv6          Resolve name to IPv6 address",
    " -#/--progress-bar  Display transfer progress as a progress bar",
    NULL
  };
  for(i=0; help[i]; i++)
    puts(help[i]);
}

struct LongShort {
  const char *letter;
  const char *lname;
  bool extraparam;
