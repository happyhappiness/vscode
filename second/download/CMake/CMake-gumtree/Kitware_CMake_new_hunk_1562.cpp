        strcmp(dent->d_name, "..") == 0)

      continue;



    snprintf(realpath, TAR_MAXPATHLEN, "%s/%s", realdir,

       dent->d_name);

    if (savedir)

      snprintf(savepath, TAR_MAXPATHLEN, "%s/%s", savedir,

         dent->d_name);



#ifndef WIN32

