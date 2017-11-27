static void *srrd_create_thread (void *targs) /* {{{ */
{
  srrd_create_args_t *args = targs;
  char tmpfile[PATH_MAX];
  int status;

  status = lock_file (args->filename);
  if (status != 0)
  {
    if (status == EEXIST)
      NOTICE ("srrd_create_thread: File \"%s\" is already being created.",
          args->filename);
    else
      ERROR ("srrd_create_thread: Unable to lock file \"%s\".",
          args->filename);
    srrd_create_args_destroy (args);
    return (0);
  }

  ssnprintf (tmpfile, sizeof (tmpfile), "%s.async", args->filename);

  status = srrd_create (tmpfile, args->pdp_step, args->last_up,
      args->argc, (void *) args->argv);
  if (status != 0)
  {
    WARNING ("srrd_create_thread: srrd_create (%s) returned status %i.",
        args->filename, status);
    unlink (tmpfile);
    unlock_file (args->filename);
    srrd_create_args_destroy (args);
    return (0);
  }

  status = rename (tmpfile, args->filename);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("srrd_create_thread: rename (\"%s\", \"%s\") failed: %s",
        tmpfile, args->filename,
        sstrerror (errno, errbuf, sizeof (errbuf)));
    unlink (tmpfile);
    unlock_file (args->filename);
    srrd_create_args_destroy (args);
    return (0);
  }

  DEBUG ("srrd_create_thread: Successfully created RRD file \"%s\".",
      args->filename);

  unlock_file (args->filename);
  srrd_create_args_destroy (args);

  return (0);
}