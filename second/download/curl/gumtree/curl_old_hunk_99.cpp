  return 0;
}

static void checkpasswd(const char *kind, /* for what purpose */
                        char **userpwd) /* pointer to allocated string */
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
