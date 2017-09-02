int Curl_parsenetrc(char *host,
                    char *login,
                    char *password)
{
  FILE *file;
  char netrcbuffer[256];
  int retcode=1;

  int specific_login = (login[0] != 0);
  
  char *home = NULL; 
  int state=NOTHING;

  char state_login=0;      /* Found a login keyword */
  char state_password=0;   /* Found a password keyword */
  char state_our_login=0;  /* With specific_login, found *our* login name */

#define NETRC DOT_CHAR "netrc"

#if defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
  struct passwd *pw;
  pw= getpwuid(geteuid());
  if (pw) {
#ifdef  VMS
    home = decc$translate_vms(pw->pw_dir);
#else
    home = pw->pw_dir;
#endif
  }
#else
  void *pw=NULL;
#endif
  
  if(NULL == pw) {
    home = curl_getenv("HOME"); /* portable environment reader */
    if(!home) {
      return -1;
    }
  }

  if(strlen(home)>(sizeof(netrcbuffer)-strlen(NETRC))) {
    if(NULL==pw)
      free(home);
    return -1;
  }

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
            /* the next tok is the machine name, this is in itself the
               delimiter that starts the stuff entered for this machine,
               after this we need to search for 'login' and
               'password'. */
            state=HOSTFOUND;
          }
          break;
        case HOSTFOUND:
          if(strequal(host, tok)) {
            /* and yes, this is our host! */
            state=HOSTVALID;
#ifdef _NETRC_DEBUG
            printf("HOST: %s\n", tok);
#endif
            retcode=0; /* we did find our host */
          }
          else
            /* not our host */
            state=NOTHING;
          break;
        case HOSTVALID:
          /* we are now parsing sub-keywords concerning "our" host */
          if(state_login) {
            if (specific_login) {
              state_our_login = strequal(login, tok);
            }else{
              strncpy(login, tok, LOGINSIZE-1);
#ifdef _NETRC_DEBUG
              printf("LOGIN: %s\n", login);
#endif
            }
            state_login=0;
          }
          else if(state_password) {
            if (state_our_login || !specific_login) {
              strncpy(password, tok, PASSWORDSIZE-1);
#ifdef _NETRC_DEBUG
              printf("PASSWORD: %s\n", password);
#endif
            }
            state_password=0;
          }
          else if(strequal("login", tok))
            state_login=1;
          else if(strequal("password", tok))
            state_password=1;
          else if(strequal("machine", tok)) {
            /* ok, there's machine here go => */
            state = HOSTFOUND;
            state_our_login = 0;
          }
          break;
        } /* switch (state) */

        tok = strtok_r(NULL, " \t\n", &tok_buf);
      } /* while (tok) */
    } /* while fgets() */

done:
    fclose(file);
  }

  if(NULL==pw)
    free(home);

  return retcode;
}