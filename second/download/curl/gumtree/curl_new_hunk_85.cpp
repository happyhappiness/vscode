{
  char *ptr = strchr(*userpwd, ':');
  if(!ptr) {
    /* no password present, prompt for one */
    char passwd[256]="";
    char prompt[256];
    size_t passwdlen;
    size_t userlen = strlen(*userpwd);
    char *passptr;

    /* build a nice-looking prompt */
    curl_msnprintf(prompt, sizeof(prompt),
                   "Enter %s password for user '%s':",
                   kind, *userpwd);

    /* get password */
    getpass_r(prompt, passwd, sizeof(passwd));
    passwdlen = strlen(passwd);

    /* extend the allocated memory area to fit the password too */
    passptr = realloc(*userpwd,
                      passwdlen + 1 + /* an extra for the colon */
                      userlen + 1);   /* an extra for the zero */

    if(passptr) {
      /* append the password separated with a colon */
      passptr[userlen]=':';
      memcpy(&passptr[userlen+1], passwd, passwdlen+1);
      *userpwd = passptr;
    }
  }
}

static ParameterError getparameter(char *flag, /* f or -long-flag */
                                   char *nextarg, /* NULL if unset */
