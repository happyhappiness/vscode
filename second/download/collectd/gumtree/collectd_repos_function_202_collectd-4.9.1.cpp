static int srrd_create (const char *filename, /* {{{ */
    unsigned long pdp_step, time_t last_up,
    int argc, const char **argv)
{
  int status;

  int new_argc;
  char **new_argv;

  char pdp_step_str[16];
  char last_up_str[16];

  new_argc = 6 + argc;
  new_argv = (char **) malloc ((new_argc + 1) * sizeof (char *));
  if (new_argv == NULL)
  {
    ERROR ("rrdtool plugin: malloc failed.");
    return (-1);
  }

  if (last_up == 0)
    last_up = time (NULL) - 10;

  ssnprintf (pdp_step_str, sizeof (pdp_step_str), "%lu", pdp_step);
  ssnprintf (last_up_str, sizeof (last_up_str), "%u", (unsigned int) last_up);

  new_argv[0] = "create";
  new_argv[1] = (void *) filename;
  new_argv[2] = "-s";
  new_argv[3] = pdp_step_str;
  new_argv[4] = "-b";
  new_argv[5] = last_up_str;

  memcpy (new_argv + 6, argv, argc * sizeof (char *));
  new_argv[new_argc] = NULL;

  pthread_mutex_lock (&librrd_lock);
  optind = 0; /* bug in librrd? */
  rrd_clear_error ();

  status = rrd_create (new_argc, new_argv);
  pthread_mutex_unlock (&librrd_lock);

  if (status != 0)
  {
    WARNING ("rrdtool plugin: rrd_create (%s) failed: %s",
        filename, rrd_get_error ());
  }

  sfree (new_argv);

  return (status);
}