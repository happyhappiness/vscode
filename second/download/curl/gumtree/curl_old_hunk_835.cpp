
  if(!netrcfile) {
    bool home_alloc = FALSE;
    char *home = curl_getenv("HOME"); /* portable environment reader */
    if(home) {
      home_alloc = TRUE;
#if defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
    }
    else {
      struct passwd *pw;
      pw= getpwuid(geteuid());
      if(pw) {
        home = pw->pw_dir;
      }
#endif
    }

    if(!home)
      return -1;

    netrcfile = curl_maprintf("%s%s%s", home, DIR_CHAR, NETRC);
    if(home_alloc)
      Curl_safefree(home);
    if(!netrcfile) {
      return -1;
