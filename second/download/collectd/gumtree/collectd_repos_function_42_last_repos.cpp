static int srrd_create(const char *filename, /* {{{ */
                       unsigned long pdp_step, time_t last_up, int argc,
                       const char **argv) {
  int status;
  char *filename_copy;

  if ((filename == NULL) || (argv == NULL))
    return -EINVAL;

  /* Some versions of librrd don't have the `const' qualifier for the first
   * argument, so we have to copy the pointer here to avoid warnings. It sucks,
   * but what else can we do? :(  -octo */
  filename_copy = strdup(filename);
  if (filename_copy == NULL) {
    ERROR("srrd_create: strdup failed.");
    return -ENOMEM;
  }

  optind = 0; /* bug in librrd? */
  rrd_clear_error();

  status = rrd_create_r(filename_copy, pdp_step, last_up, argc, (void *)argv);

  if (status != 0) {
    WARNING("rrdtool plugin: rrd_create_r (%s) failed: %s", filename,
            rrd_get_error());
  }

  sfree(filename_copy);

  return status;
}