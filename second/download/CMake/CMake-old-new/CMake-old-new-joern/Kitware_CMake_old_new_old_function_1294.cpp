void
th_print_long_ls(TAR *t)
{
  char modestring[12];
#ifndef WIN32
  struct passwd *pw;
  struct group *gr;
#endif
  uid_t uid;
  gid_t gid;
  char username[_POSIX_LOGIN_NAME_MAX];
  char groupname[_POSIX_LOGIN_NAME_MAX];
  time_t mtime;
  struct tm *mtm;

#ifdef HAVE_STRFTIME
  char timebuf[18];
#else
  const char *months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };
#endif

  uid = th_get_uid(t);
#ifndef WIN32
  pw = getpwuid(uid);
  if (pw != NULL)
    strlcpy(username, pw->pw_name, sizeof(username));
  else
#endif
    snprintf(username, sizeof(username), "%d", uid);
  gid = th_get_gid(t);
#ifndef WIN32
  gr = getgrgid(gid);
  if (gr != NULL)
    strlcpy(groupname, gr->gr_name, sizeof(groupname));
  else
#endif
    snprintf(groupname, sizeof(groupname), "%d", gid);
    
  strmode(th_get_mode(t), modestring);
  printf("%.10s %-8.8s %-8.8s ", modestring, username, groupname);

#ifndef WIN32
  if (TH_ISCHR(t) || TH_ISBLK(t))
    printf(" %3d, %3d ", th_get_devmajor(t), th_get_devminor(t));
  else
    printf("%9ld ", (long)th_get_size(t));
#endif

  mtime = th_get_mtime(t);
  mtm = localtime(&mtime);
#ifdef HAVE_STRFTIME
  strftime(timebuf, sizeof(timebuf), "%h %e %H:%M %Y", mtm);
  printf("%s", timebuf);
#else
  printf("%.3s %2d %2d:%02d %4d",
         months[mtm->tm_mon],
         mtm->tm_mday, mtm->tm_hour, mtm->tm_min, mtm->tm_year + 1900);
#endif

  printf(" %s", th_get_pathname(t));

#ifndef _WIN32
  if (TH_ISSYM(t) || TH_ISLNK(t))
  {
    if (TH_ISSYM(t))
      printf(" -> ");
    else
      printf(" link to ");
    if ((t->options & TAR_GNU) && t->th_buf.gnu_longlink != NULL)
      printf("%s", t->th_buf.gnu_longlink);
    else
      printf("%.100s", t->th_buf.linkname);
  }
#endif

  putchar('\n');
}