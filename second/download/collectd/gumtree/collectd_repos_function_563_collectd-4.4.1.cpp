static int c_ipmi_init (void)
{
  int status;

  c_ipmi_active = 1;

  status = pthread_create (&thread_id, /* attr = */ NULL, thread_main,
      /* user data = */ NULL);
  if (status != 0)
  {
    c_ipmi_active = 0;
    thread_id = (pthread_t) 0;
    ERROR ("ipmi plugin: pthread_create failed.");
    return (-1);
  }

  return (0);
}