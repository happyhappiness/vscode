static int mc_receive_thread_stop(void) /* {{{ */
{
  if (mc_receive_thread_running == 0)
    return -1;

  mc_receive_thread_loop = 0;

  INFO("gmond plugin: Stopping receive thread.");
  pthread_kill(mc_receive_thread_id, SIGTERM);
  pthread_join(mc_receive_thread_id, /* return value = */ NULL);
  memset(&mc_receive_thread_id, 0, sizeof(mc_receive_thread_id));

  mc_receive_thread_running = 0;

  return 0;
}