int plugin_load(char const *plugin_name, uint32_t flags) {
  DIR *dh;
  const char *dir;
  char filename[BUFSIZE] = "";
  char typename[BUFSIZE];
  int ret;
  struct stat statbuf;
  struct dirent *de;
  int status;

  if (plugin_name == NULL)
    return (EINVAL);

  /* Check if plugin is already loaded and don't do anything in this
   * case. */
  if (plugin_is_loaded(plugin_name))
    return (0);

  dir = plugin_get_dir();
  ret = 1;

  /*
   * XXX: Magic at work:
   *
   * Some of the language bindings, for example the Python and Perl
   * plugins, need to be able to export symbols to the scripts they run.
   * For this to happen, the "Globals" flag needs to be set.
   * Unfortunately, this technical detail is hard to explain to the
   * average user and she shouldn't have to worry about this, ideally.
   * So in order to save everyone's sanity use a different default for a
   * handful of special plugins. --octo
   */
  if ((strcasecmp("perl", plugin_name) == 0) ||
      (strcasecmp("python", plugin_name) == 0))
    flags |= PLUGIN_FLAGS_GLOBAL;

  /* `cpu' should not match `cpufreq'. To solve this we add `.so' to the
   * type when matching the filename */
  status = ssnprintf(typename, sizeof(typename), "%s.so", plugin_name);
  if ((status < 0) || ((size_t)status >= sizeof(typename))) {
    WARNING("plugin_load: Filename too long: \"%s.so\"", plugin_name);
    return (-1);
  }

  if ((dh = opendir(dir)) == NULL) {
    char errbuf[1024];
    ERROR("plugin_load: opendir (%s) failed: %s", dir,
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return (-1);
  }

  while ((de = readdir(dh)) != NULL) {
    if (strcasecmp(de->d_name, typename))
      continue;

    status = ssnprintf(filename, sizeof(filename), "%s/%s", dir, de->d_name);
    if ((status < 0) || ((size_t)status >= sizeof(filename))) {
      WARNING("plugin_load: Filename too long: \"%s/%s\"", dir, de->d_name);
      continue;
    }

    if (lstat(filename, &statbuf) == -1) {
      char errbuf[1024];
      WARNING("plugin_load: stat (\"%s\") failed: %s", filename,
              sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    } else if (!S_ISREG(statbuf.st_mode)) {
      /* don't follow symlinks */
      WARNING("plugin_load: %s is not a regular file.", filename);
      continue;
    }

    status = plugin_load_file(filename, flags);
    if (status == 0) {
      /* success */
      plugin_mark_loaded(plugin_name);
      ret = 0;
      INFO("plugin_load: plugin \"%s\" successfully loaded.", plugin_name);
      break;
    } else {
      ERROR("plugin_load: Load plugin \"%s\" failed with "
            "status %i.",
            plugin_name, status);
    }
  }

  closedir(dh);

  if (filename[0] == 0)
    ERROR("plugin_load: Could not find plugin \"%s\" in %s", plugin_name, dir);

  return (ret);
}