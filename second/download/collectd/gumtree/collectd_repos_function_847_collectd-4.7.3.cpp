static int c_ipmi_shutdown (void)
{
  c_ipmi_active = 0;

  if (thread_id != (pthread_t) 0)
  {
    pthread_join (thread_id, NULL);
    thread_id = (pthread_t) 0;
  }

  sensor_list_remove_all ();

  return (0);
}