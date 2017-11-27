int main (int argc, char **argv) /* {{{ */
{
  int i;
  time_t last_time;
  int values_sent = 0;

  read_options (argc, argv);

  sigint_action.sa_handler = signal_handler;
  sigaction (SIGINT, &sigint_action, /* old = */ NULL);

  sigterm_action.sa_handler = signal_handler;
  sigaction (SIGTERM, &sigterm_action, /* old = */ NULL);


  values_heap = c_heap_create (compare_time);
  if (values_heap == NULL)
  {
    fprintf (stderr, "c_heap_create failed.\n");
    exit (EXIT_FAILURE);
  }

  net = lcc_network_create ();
  if (net == NULL)
  {
    fprintf (stderr, "lcc_network_create failed.\n");
    exit (EXIT_FAILURE);
  }
  else
  {
    lcc_server_t *srv;
    
    srv = lcc_server_create (net, conf_destination, conf_service);
    if (srv == NULL)
    {
      fprintf (stderr, "lcc_server_create failed.\n");
      exit (EXIT_FAILURE);
    }

    lcc_server_set_ttl (srv, 42);
#if 0
    lcc_server_set_security_level (srv, ENCRYPT,
        "admin", "password1");
#endif
  }

  fprintf (stdout, "Creating %i values ... ", conf_num_values);
  fflush (stdout);
  for (i = 0; i < conf_num_values; i++)
  {
    lcc_value_list_t *vl;

    vl = create_value_list ();
    if (vl == NULL)
    {
      fprintf (stderr, "create_value_list failed.\n");
      exit (EXIT_FAILURE);
    }

    c_heap_insert (values_heap, vl);
  }
  fprintf (stdout, "done\n");

  last_time = 0;
  while (loop)
  {
    lcc_value_list_t *vl = c_heap_get_root (values_heap);

    if (vl == NULL)
      break;

    if (vl->time != last_time)
    {
      printf ("%i values have been sent.\n", values_sent);

      /* Check if we need to sleep */
      time_t now = time (NULL);

      while (now < vl->time)
      {
        /* 1 / 100 second */
        struct timespec ts = { 0, 10000000 };
        nanosleep (&ts, /* remaining = */ NULL);
        now = time (NULL);

        if (!loop)
          break;
      }
      last_time = vl->time;
    }

    send_value (vl);
    values_sent++;

    c_heap_insert (values_heap, vl);
  }

  fprintf (stdout, "Shutting down.\n");
  fflush (stdout);

  while (42)
  {
    lcc_value_list_t *vl = c_heap_get_root (values_heap);
    if (vl == NULL)
      break;
    destroy_value_list (vl);
  }
  c_heap_destroy (values_heap);

  lcc_network_destroy (net);
  exit (EXIT_SUCCESS);
  return (0);
}