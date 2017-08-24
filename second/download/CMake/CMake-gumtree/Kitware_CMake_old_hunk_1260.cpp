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
