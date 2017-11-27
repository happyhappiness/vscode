static int read_syshugepages(const char *path, const char *node) {
  static const char hugepages_dir[] = "hugepages-";
  DIR *dir;
  struct dirent *result;
  char path2[PATH_MAX];

  dir = opendir(path);
  if (dir == NULL) {
    ERROR("%s: cannot open directory %s", g_plugin_name, path);
    return -1;
  }

  /* read "hugepages-XXXXXkB" entries */
  while ((result = readdir(dir)) != NULL) {
    if (strncmp(result->d_name, hugepages_dir, sizeof(hugepages_dir) - 1)) {
      /* not node dir */
      errno = 0;
      continue;
    }

    long page_size = strtol(result->d_name + strlen(hugepages_dir),
                            /* endptr = */ NULL, /* base = */ 10);
    if (errno != 0) {
      char errbuf[1024];
      ERROR("%s: failed to determine page size from directory name \"%s\": %s",
            g_plugin_name, result->d_name,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }

    /* /sys/devices/system/node/node?/hugepages/ */
    snprintf(path2, sizeof(path2), "%s/%s", path, result->d_name);

    walk_directory(path2, read_hugepage_entry,
                   &(struct entry_info){
                       .d_name = result->d_name,
                       .node = node,
                       .page_size_kb = (size_t)page_size,
                   },
                   /* hidden = */ 0);
    errno = 0;
  }

  /* Check if NULL return from readdir() was an error */
  if (errno != 0) {
    ERROR("%s: readdir failed", g_plugin_name);
    closedir(dir);
    return -1;
  }

  closedir(dir);
  return 0;
}