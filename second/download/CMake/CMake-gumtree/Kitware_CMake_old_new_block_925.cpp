f(file) {
    char *tok;
        char *tok_buf;
    while(fgets(netrcbuffer, sizeof(netrcbuffer), file)) {
      tok=strtok_r(netrcbuffer, " \t\n", &tok_buf);
      while(tok) {
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
            strncpy(login, tok, LOGINSIZE-1);
#ifdef _NETRC_DEBUG
            printf("LOGIN: %s\n", login);
#endif
            state_login=0;
          }
          else if(state_password) {
            strncpy(password, tok, PASSWORDSIZE-1);
#ifdef _NETRC_DEBUG
            printf("PASSWORD: %s\n", password);
#endif
            state_password=0;
          }
          else if(strequal("login", tok))
            state_login=1;
          else if(strequal("password", tok))
            state_password=1;
          else if(strequal("machine", tok)) {
            /* ok, there's machine here go => */
            state = HOSTFOUND;
          }
          break;
        } /* switch (state) */
        tok = strtok_r(NULL, " \t\n", &tok_buf);
      } /* while (tok) */
    } /* while fgets() */

    fclose(file);
  }