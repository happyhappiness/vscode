static int vserver_read(void) {
  DIR *proc;

  errno = 0;
  proc = opendir(PROCDIR);
  if (proc == NULL) {
    char errbuf[1024];
    ERROR("vserver plugin: fopen (%s): %s", PROCDIR,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  while (42) {
    struct dirent *dent;
    int len;
    char file[BUFSIZE];

    FILE *fh;
    char buffer[BUFSIZE];

    struct stat statbuf;
    char *cols[4];

    int status;

    errno = 0;
    dent = readdir(proc);
    if (dent == NULL) {
      char errbuf[4096];

      if (errno == 0) /* end of directory */
        break;

      ERROR("vserver plugin: failed to read directory %s: %s", PROCDIR,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      closedir(proc);
      return -1;
    }

    if (dent->d_name[0] == '.')
      continue;

    len = snprintf(file, sizeof(file), PROCDIR "/%s", dent->d_name);
    if ((len < 0) || (len >= BUFSIZE))
      continue;

    status = stat(file, &statbuf);
    if (status != 0) {
      char errbuf[4096];
      WARNING("vserver plugin: stat (%s) failed: %s", file,
              sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    if (!S_ISDIR(statbuf.st_mode))
      continue;

    /* socket message accounting */
    len = snprintf(file, sizeof(file), PROCDIR "/%s/cacct", dent->d_name);
    if ((len < 0) || ((size_t)len >= sizeof(file)))
      continue;

    if (NULL == (fh = fopen(file, "r"))) {
      char errbuf[1024];
      ERROR("Cannot open '%s': %s", file,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    }

    while ((fh != NULL) && (NULL != fgets(buffer, BUFSIZE, fh))) {
      derive_t rx;
      derive_t tx;
      const char *type_instance;

      if (strsplit(buffer, cols, 4) < 4)
        continue;

      if (0 == strcmp(cols[0], "UNIX:"))
        type_instance = "unix";
      else if (0 == strcmp(cols[0], "INET:"))
        type_instance = "inet";
      else if (0 == strcmp(cols[0], "INET6:"))
        type_instance = "inet6";
      else if (0 == strcmp(cols[0], "OTHER:"))
        type_instance = "other";
      else if (0 == strcmp(cols[0], "UNSPEC:"))
        type_instance = "unspec";
      else
        continue;

      rx = vserver_get_sock_bytes(cols[1]);
      tx = vserver_get_sock_bytes(cols[2]);
      /* cols[3] == errors */

      traffic_submit(dent->d_name, type_instance, rx, tx);
    } /* while (fgets) */

    if (fh != NULL) {
      fclose(fh);
      fh = NULL;
    }

    /* thread information and load */
    len = snprintf(file, sizeof(file), PROCDIR "/%s/cvirt", dent->d_name);
    if ((len < 0) || ((size_t)len >= sizeof(file)))
      continue;

    if (NULL == (fh = fopen(file, "r"))) {
      char errbuf[1024];
      ERROR("Cannot open '%s': %s", file,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    }

    while ((fh != NULL) && (NULL != fgets(buffer, BUFSIZE, fh))) {
      int n = strsplit(buffer, cols, 4);

      if (2 == n) {
        const char *type_instance;
        gauge_t value;

        if (0 == strcmp(cols[0], "nr_threads:"))
          type_instance = "total";
        else if (0 == strcmp(cols[0], "nr_running:"))
          type_instance = "running";
        else if (0 == strcmp(cols[0], "nr_unintr:"))
          type_instance = "uninterruptable";
        else if (0 == strcmp(cols[0], "nr_onhold:"))
          type_instance = "onhold";
        else
          continue;

        value = atof(cols[1]);
        submit_gauge(dent->d_name, "vs_threads", type_instance, value);
      } else if (4 == n) {
        if (0 == strcmp(cols[0], "loadavg:")) {
          gauge_t snum = atof(cols[1]);
          gauge_t mnum = atof(cols[2]);
          gauge_t lnum = atof(cols[3]);
          load_submit(dent->d_name, snum, mnum, lnum);
        }
      }
    } /* while (fgets) */

    if (fh != NULL) {
      fclose(fh);
      fh = NULL;
    }

    /* processes and memory usage */
    len = snprintf(file, sizeof(file), PROCDIR "/%s/limit", dent->d_name);
    if ((len < 0) || ((size_t)len >= sizeof(file)))
      continue;

    if (NULL == (fh = fopen(file, "r"))) {
      char errbuf[1024];
      ERROR("Cannot open '%s': %s", file,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    }

    while ((fh != NULL) && (NULL != fgets(buffer, BUFSIZE, fh))) {
      const char *type = "vs_memory";
      const char *type_instance;
      gauge_t value;

      if (strsplit(buffer, cols, 2) < 2)
        continue;

      if (0 == strcmp(cols[0], "PROC:")) {
        type = "vs_processes";
        type_instance = "";
        value = atof(cols[1]);
      } else {
        if (0 == strcmp(cols[0], "VM:"))
          type_instance = "vm";
        else if (0 == strcmp(cols[0], "VML:"))
          type_instance = "vml";
        else if (0 == strcmp(cols[0], "RSS:"))
          type_instance = "rss";
        else if (0 == strcmp(cols[0], "ANON:"))
          type_instance = "anon";
        else
          continue;

        value = atof(cols[1]) * pagesize;
      }

      submit_gauge(dent->d_name, type, type_instance, value);
    } /* while (fgets) */

    if (fh != NULL) {
      fclose(fh);
      fh = NULL;
    }
  } /* while (readdir) */

  closedir(proc);

  return 0;
}