static int srrd_update(char *filename, char *template, int argc,
                       const char **argv) {
  int status;

  optind = 0; /* bug in librrd? */
  rrd_clear_error();

  status = rrd_update_r(filename, template, argc, (void *)argv);

  if (status != 0) {
    WARNING("rrdtool plugin: rrd_update_r (%s) failed: %s", filename,
            rrd_get_error());
  }

  return (status);
}