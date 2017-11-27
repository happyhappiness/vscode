static int mc_receive_thread_start (void) /* {{{ */
{
  int status;

  if (mc_receive_thread_running != 0)
    return (-1);

  mc_receive_thread_loop = 1;

  status = pthread_create (&mc_receive_thread_id, /* attr = */ NULL,
      mc_receive_thread, /* args = */ NULL);
  if (status != 0)
  {
    ERROR ("gmond plugin: Starting receive thread failed.");
    mc_receive_thread_loop = 0;
    return (-1);
  }

  mc_receive_thread_running = 1;
  return (0);
}