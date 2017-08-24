        strcmp(dent->d_name, "..") == 0)
      continue;

    snprintf(realpath, MAXPATHLEN, "%s/%s", realdir,
       dent->d_name);
    if (savedir)
      snprintf(savepath, MAXPATHLEN, "%s/%s", savedir,
         dent->d_name);

#ifndef WIN32
