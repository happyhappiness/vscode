int
tar_append_tree(TAR *t, char *realdir, char *savedir)
{
  char realpath[MAXPATHLEN];
  char savepath[MAXPATHLEN];
#ifndef _MSC_VER
  struct dirent *dent;
  DIR *dp;
#else  
  kwDirEntry * dent;
  kwDirectory *dp;
#endif  
  struct stat s;

#ifdef DEBUG
  printf("==> tar_append_tree(0x%lx, \"%s\", \"%s\")\n",
         t, realdir, (savedir ? savedir : "[NULL]"));
#endif

  if (tar_append_file(t, realdir, savedir) != 0)
    return -1;

#ifdef DEBUG
  puts("    tar_append_tree(): done with tar_append_file()...");
#endif

#ifdef _MSC_VER
  dp = kwOpenDir(realdir);
#else
  dp = opendir(realdir);
#endif

  if (dp == NULL)
  {
    if (errno == ENOTDIR)
      return 0;
    return -1;
  }
#ifdef _MSC_VER
  while ((dent = kwReadDir(dp)) != NULL)
#else
  while ((dent = readdir(dp)) != NULL)
#endif
  {
    if (strcmp(dent->d_name, ".") == 0 ||
        strcmp(dent->d_name, "..") == 0)
      continue;

    snprintf(realpath, MAXPATHLEN, "%s/%s", realdir,
       dent->d_name);
    if (savedir)
      snprintf(savepath, MAXPATHLEN, "%s/%s", savedir,
         dent->d_name);

#ifndef WIN32
    if (lstat(realpath, &s) != 0)
      return -1;
#else
    if (stat(realpath, &s) != 0)
      return -1;
#endif
    if (S_ISDIR(s.st_mode))
    {
      if (tar_append_tree(t, realpath,
              (savedir ? savepath : NULL)) != 0)
        return -1;
      continue;
    }

    if (tar_append_file(t, realpath,
            (savedir ? savepath : NULL)) != 0)
      return -1;
  }

#ifdef _MSC_VER
  kwCloseDir(dp);
#else
  closedir(dp);
#endif

  return 0;
}