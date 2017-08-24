f(capath) {
    struct_stat st;
    if(stat(capath, &st) == -1)
      return CURLE_SSL_CACERT_BADFILE;

    if(S_ISDIR(st.st_mode)) {
      PRDirEntry *entry;
      PRDir *dir = PR_OpenDir(capath);
      if(!dir)
        return CURLE_SSL_CACERT_BADFILE;

      while((entry = PR_ReadDir(dir, PR_SKIP_BOTH | PR_SKIP_HIDDEN))) {
        char *fullpath = aprintf("%s/%s", capath, entry->name);
        if(!fullpath) {
          PR_CloseDir(dir);
          return CURLE_OUT_OF_MEMORY;
        }

        if(CURLE_OK != nss_load_cert(&conn->ssl[sockindex], fullpath, PR_TRUE))
          /* This is purposefully tolerant of errors so non-PEM files can
           * be in the same directory */
          infof(data, "failed to load '%s' from CURLOPT_CAPATH\n", fullpath);

        free(fullpath);
      }

      PR_CloseDir(dir);
    }
    else
      infof(data, "warning: CURLOPT_CAPATH not a directory (%s)\n", capath);
  }