static int srrd_update(char *filename, char *template, int argc,
                       const char **argv) {
  int status;

  int new_argc;
  char **new_argv;

  assert(template == NULL);

  new_argc = 2 + argc;
  new_argv = malloc((new_argc + 1) * sizeof(*new_argv));
  if (new_argv == NULL) {
    ERROR("rrdtool plugin: malloc failed.");
    return (-1);
  }

  new_argv[0] = "update";
  new_argv[1] = filename;

  memcpy(new_argv + 2, argv, argc * sizeof(char *));
  new_argv[new_argc] = NULL;

  pthread_mutex_lock(&librrd_lock);
  optind = 0; /* bug in librrd? */
  rrd_clear_error();

  status = rrd_update(new_argc, new_argv);
  pthread_mutex_unlock(&librrd_lock);

  if (status != 0) {
    WARNING("rrdtool plugin: rrd_update_r failed: %s: %s", filename,
            rrd_get_error());
  }

  sfree(new_argv);

  return (status);
}