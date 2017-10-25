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

   if (pw) {
#ifdef VMS
     home = decc$translate_vms(pw->pw_dir);
#else
     home = pw->pw_dir;
#endif
     if (home && home[0])
       home = strdup(home);
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