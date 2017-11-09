char *homedir(void)
{
  char *home;

  home = GetEnv("CURL_HOME", FALSE);
  if(home)
    return home;

  home = GetEnv("HOME", FALSE);
  if(home)
    return home;

#if defined(HAVE_GETPWUID) && defined(HAVE_GETEUID)
 {
   struct passwd *pw = getpwuid(geteuid());

   if(pw) {
     home = pw->pw_dir;
     if(home && home[0])
       home = strdup(home);
     else
       home = NULL;
   }
 }
#endif /* PWD-stuff */
#ifdef WIN32
  home = GetEnv("APPDATA", TRUE);
  if(!home)
    home = GetEnv("%USERPROFILE%\\Application Data", TRUE); /* Normally only
                                                               on Win-2K/XP */
#endif /* WIN32 */
  return home;
}