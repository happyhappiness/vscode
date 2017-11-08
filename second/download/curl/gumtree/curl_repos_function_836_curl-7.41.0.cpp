static char *GetEnv(const char *variable, char do_expand)
{
  char *env = NULL;
#ifdef WIN32
  char  buf1[1024], buf2[1024];
  DWORD rc;

  /* Don't use getenv(); it doesn't find variable added after program was
   * started. Don't accept truncated results (i.e. rc >= sizeof(buf1)).  */

  rc = GetEnvironmentVariable(variable, buf1, sizeof(buf1));
  if(rc > 0 && rc < sizeof(buf1)) {
    env = buf1;
    variable = buf1;
  }
  if(do_expand && strchr(variable,'%')) {
    /* buf2 == variable if not expanded */
    rc = ExpandEnvironmentStrings (variable, buf2, sizeof(buf2));
    if(rc > 0 && rc < sizeof(buf2) &&
       !strchr(buf2,'%'))    /* no vars still unexpanded */
      env = buf2;
  }
#else
  (void)do_expand;
  /* no length control */
  env = getenv(variable);
#endif
  return (env && env[0]) ? strdup(env) : NULL;
}