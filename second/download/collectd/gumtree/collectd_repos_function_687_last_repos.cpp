static int ps_read_tasks_status(process_entry_t *ps) {
  char dirname[64];
  DIR *dh;
  char filename[64];
  FILE *fh;
  struct dirent *ent;
  derive_t cswitch_vol = 0;
  derive_t cswitch_invol = 0;
  char buffer[1024];
  char *fields[8];
  int numfields;

  snprintf(dirname, sizeof(dirname), "/proc/%li/task", ps->id);

  if ((dh = opendir(dirname)) == NULL) {
    DEBUG("Failed to open directory `%s'", dirname);
    return -1;
  }

  while ((ent = readdir(dh)) != NULL) {
    char *tpid;

    if (!isdigit((int)ent->d_name[0]))
      continue;

    tpid = ent->d_name;

    if (snprintf(filename, sizeof(filename), "/proc/%li/task/%s/status", ps->id,
                 tpid) >= sizeof(filename)) {
      DEBUG("Filename too long: `%s'", filename);
      continue;
    }

    if ((fh = fopen(filename, "r")) == NULL) {
      DEBUG("Failed to open file `%s'", filename);
      continue;
    }

    while (fgets(buffer, sizeof(buffer), fh) != NULL) {
      derive_t tmp;
      char *endptr;

      if (strncmp(buffer, "voluntary_ctxt_switches", 23) != 0 &&
          strncmp(buffer, "nonvoluntary_ctxt_switches", 26) != 0)
        continue;

      numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));

      if (numfields < 2)
        continue;

      errno = 0;
      endptr = NULL;
      tmp = (derive_t)strtoll(fields[1], &endptr, /* base = */ 10);
      if ((errno == 0) && (endptr != fields[1])) {
        if (strncmp(buffer, "voluntary_ctxt_switches", 23) == 0) {
          cswitch_vol += tmp;
        } else if (strncmp(buffer, "nonvoluntary_ctxt_switches", 26) == 0) {
          cswitch_invol += tmp;
        }
      }
    } /* while (fgets) */

    if (fclose(fh)) {
      char errbuf[1024];
      WARNING("processes: fclose: %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
    }
  }
  closedir(dh);

  ps->cswitch_vol = cswitch_vol;
  ps->cswitch_invol = cswitch_invol;

  return 0;
}