
  sprintf(netrcbuffer, "%s%s%s", home, DIR_CHAR, NETRC);

#ifdef MALLOCDEBUG
  {
    /* This is a hack to allow testing.
     * If compiled with --enable-debug and CURL_DEBUG_NETRC is defined,
     * then it's the path to a substitute .netrc for testing purposes *only* */

    char *override = curl_getenv("CURL_DEBUG_NETRC");

    if (override != NULL) {
      printf("NETRC: overridden .netrc file: %s\n", home);

      if (strlen(override)+1 > sizeof(netrcbuffer)) {
        free(override);
        if(NULL==pw)
          free(home);

        return -1;
      }
      strcpy(netrcbuffer, override);
      free(override);
    }
  }
#endif /* MALLOCDEBUG */

  file = fopen(netrcbuffer, "r");
  if(file) {
    char *tok;
        char *tok_buf;
    while(fgets(netrcbuffer, sizeof(netrcbuffer), file)) {
      tok=strtok_r(netrcbuffer, " \t\n", &tok_buf);
      while(tok) {

        if (login[0] && password[0])
          goto done;

        switch(state) {
        case NOTHING:
          if(strequal("machine", tok)) {
