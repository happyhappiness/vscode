static int srrd_create_async (const char *filename, /* {{{ */
    unsigned long pdp_step, time_t last_up,
    int argc, const char **argv)
{
  srrd_create_args_t *args;
  pthread_t thread;
  pthread_attr_t attr;
  int status;

  DEBUG ("srrd_create_async: Creating \"%s\" in the background.", filename);

  args = srrd_create_args_create (filename, pdp_step, last_up, argc, argv);
  if (args == NULL)
    return (-1);

  status = pthread_attr_init (&attr);
  if (status != 0)
  {
    srrd_create_args_destroy (args);
    return (-1);
  }

  status = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  if (status != 0)
  {
    pthread_attr_destroy (&attr);
    srrd_create_args_destroy (args);
    return (-1);
  }

  status = pthread_create (&thread, &attr, srrd_create_thread, args);
  if (status != 0)
  {
    char errbuf[1024];
    ERROR ("srrd_create_async: pthread_create failed: %s",
        sstrerror (status, errbuf, sizeof (errbuf)));
    pthread_attr_destroy (&attr);
    srrd_create_args_destroy (args);
    return (status);
  }

  pthread_attr_destroy (&attr);
  /* args is freed in srrd_create_thread(). */
  return (0);
}