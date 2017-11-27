static void *thread_main (void *user_data)
{
  int status;
  os_handler_t *os_handler = NULL;

  status = thread_init (&os_handler);
  if (status != 0)
  {
    ERROR ("ipmi plugin: thread_init failed.\n");
    return ((void *) -1);
  }

  while (c_ipmi_active != 0)
  {
    struct timeval tv = { 1, 0 };
    os_handler->perform_one_op (os_handler, &tv);
  }

  ipmi_posix_thread_free_os_handler (os_handler);

  return ((void *) 0);
}