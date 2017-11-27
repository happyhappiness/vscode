static int thread_init (os_handler_t **ret_os_handler)
{
  os_handler_t *os_handler;
  ipmi_con_t *smi_connection = NULL;
  ipmi_domain_id_t domain_id;
  int status;

  os_handler = ipmi_posix_thread_setup_os_handler (SIGIO);
  if (os_handler == NULL)
  {
    ERROR ("ipmi plugin: ipmi_posix_thread_setup_os_handler failed.");
    return (-1);
  }

  ipmi_init (os_handler);

  status = ipmi_smi_setup_con (/* if_num = */ 0,
      os_handler,
      /* user data = */ NULL,
      &smi_connection);
  if (status != 0)
  {
    c_ipmi_error ("ipmi_smi_setup_con", status);
    return (-1);
  }

  ipmi_open_option_t open_option[1] = {
    [0] = {
      .option = IPMI_OPEN_OPTION_ALL,
      { .ival = 1 }
    }
  };

  status = ipmi_open_domain ("mydomain", &smi_connection, /* num_con = */ 1,
      domain_connection_change_handler, /* user data = */ NULL,
      /* domain_fully_up_handler = */ NULL, /* user data = */ NULL,
      open_option, sizeof (open_option) / sizeof (open_option[0]),
      &domain_id);
  if (status != 0)
  {
    c_ipmi_error ("ipmi_open_domain", status);
    return (-1);
  }

  *ret_os_handler = os_handler;
  return (0);
}