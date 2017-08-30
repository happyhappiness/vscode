
  sprintf(netrcbuffer, "%s%s%s", home, DIR_CHAR, NETRC);

  file = fopen(netrcbuffer, "r");
  if(file) {
    char *tok;
        char *tok_buf;
    while(fgets(netrcbuffer, sizeof(netrcbuffer), file)) {
      tok=strtok_r(netrcbuffer, " \t\n", &tok_buf);
      while(tok) {
        switch(state) {
        case NOTHING:
          if(strequal("machine", tok)) {
