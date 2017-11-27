static int cgps_shutdown (void)
{
  void * res;

  pthread_mutex_lock (&cgps_thread_lock);
  cgps_thread_shutdown = CGPS_TRUE;
  pthread_mutex_unlock (&cgps_thread_lock);

  pthread_join(cgps_thread_id, &res);
  free(res);

  // Clean mutex:
  pthread_mutex_unlock(&cgps_thread_lock);
  pthread_mutex_destroy(&cgps_thread_lock);
  pthread_mutex_unlock(&cgps_data_lock);
  pthread_mutex_destroy(&cgps_data_lock);

  sfree (cgps_config_data.port);
  sfree (cgps_config_data.host);

  return (0);
}