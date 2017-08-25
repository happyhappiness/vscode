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