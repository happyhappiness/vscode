static int read_cpuacct_procs(const char *dirname, char const *cgroup_name,
                              void *user_data) {
  char abs_path[PATH_MAX];
  struct stat statbuf;
  char buf[1024];
  int status;

  FILE *fh;

  if (ignorelist_match(il_cgroup, cgroup_name))
    return 0;

  snprintf(abs_path, sizeof(abs_path), "%s/%s", dirname, cgroup_name);

  status = lstat(abs_path, &statbuf);
  if (status != 0) {
    ERROR("cgroups plugin: stat (\"%s\") failed.", abs_path);
    return -1;
  }

  /* We are only interested in directories, so skip everything else. */
  if (!S_ISDIR(statbuf.st_mode))
    return 0;

  snprintf(abs_path, sizeof(abs_path), "%s/%s/cpuacct.stat", dirname,
           cgroup_name);
  fh = fopen(abs_path, "r");
  if (fh == NULL) {
    char errbuf[1024];
    ERROR("cgroups plugin: fopen (\"%s\") failed: %s", abs_path,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  while (fgets(buf, sizeof(buf), fh) != NULL) {
    char *fields[8];
    int numfields = 0;
    char *key;
    size_t key_len;
    value_t value;

    /* Expected format:
     *
     *   user: 12345
     *   system: 23456
     *
     * Or:
     *
     *   user 12345
     *   system 23456
     */
    strstripnewline(buf);
    numfields = strsplit(buf, fields, STATIC_ARRAY_SIZE(fields));
    if (numfields != 2)
      continue;

    key = fields[0];
    key_len = strlen(key);
    if (key_len < 2)
      continue;

    /* Strip colon off the first column, if found */
    if (key[key_len - 1] == ':')
      key[key_len - 1] = 0;

    status = parse_value(fields[1], &value, DS_TYPE_DERIVE);
    if (status != 0)
      continue;

    cgroups_submit_one(cgroup_name, key, value);
  }

  fclose(fh);
  return 0;
}