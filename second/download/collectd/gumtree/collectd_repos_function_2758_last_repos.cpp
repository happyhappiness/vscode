int configure_collectd(struct cmdline_config *config) {
  const char *basedir;
  /*
   * Read options from the config file, the environment and the command
   * line (in that order, with later options overwriting previous ones in
   * general).
   * Also, this will automatically load modules.
   */
  if (cf_read(config->configfile)) {
    fprintf(stderr, "Error: Reading the config file failed!\n"
                    "Read the logs for details.\n");
    return 1;
  }

  /*
   * Change directory. We do this _after_ reading the config and loading
   * modules to relative paths work as expected.
   */
  if ((basedir = global_option_get("BaseDir")) == NULL) {
    fprintf(stderr,
            "Don't have a basedir to use. This should not happen. Ever.");
    return 1;
  } else if (change_basedir(basedir, config->create_basedir)) {
    fprintf(stderr, "Error: Unable to change to directory `%s'.\n", basedir);
    return 1;
  }

  /*
   * Set global variables or, if that fails, exit. We cannot run with
   * them being uninitialized. If nothing is configured, then defaults
   * are being used. So this means that the user has actually done
   * something wrong.
   */
  if (init_global_variables() != 0)
    return 1;

  return 0;
}