static void *mc_receive_thread (void *arg) /* {{{ */
{
  socket_entry_t *mc_receive_socket_entries;
  int status;
  size_t i;

  mc_receive_socket_entries = NULL;
  status = create_sockets (&mc_receive_socket_entries, &mc_receive_sockets_num,
      (mc_receive_group != NULL) ? mc_receive_group : MC_RECEIVE_GROUP_DEFAULT,
      (mc_receive_port != NULL) ? mc_receive_port : MC_RECEIVE_PORT_DEFAULT,
      /* listen = */ 1);
  if (status != 0)
  {
    ERROR ("gmond plugin: create_sockets failed.");
    return ((void *) -1);
  }

  mc_receive_sockets = (struct pollfd *) calloc (mc_receive_sockets_num,
      sizeof (*mc_receive_sockets));
  if (mc_receive_sockets == NULL)
  {
    ERROR ("gmond plugin: calloc failed.");
    for (i = 0; i < mc_receive_sockets_num; i++)
      close (mc_receive_socket_entries[i].fd);
    free (mc_receive_socket_entries);
    mc_receive_socket_entries = NULL;
    mc_receive_sockets_num = 0;
    return ((void *) -1);
  }

  for (i = 0; i < mc_receive_sockets_num; i++)
  {
    mc_receive_sockets[i].fd = mc_receive_socket_entries[i].fd;
    mc_receive_sockets[i].events = POLLIN | POLLPRI;
    mc_receive_sockets[i].revents = 0;
  }

  while (mc_receive_thread_loop != 0)
  {
    status = poll (mc_receive_sockets, mc_receive_sockets_num, -1);
    if (status <= 0)
    {
      char errbuf[1024];
      if (errno == EINTR)
        continue;
      ERROR ("gmond plugin: poll failed: %s",
          sstrerror (errno, errbuf, sizeof (errbuf)));
      break;
    }

    for (i = 0; i < mc_receive_sockets_num; i++)
    {
      if (mc_receive_sockets[i].revents != 0)
        mc_handle_socket (mc_receive_sockets + i);
    }
  } /* while (mc_receive_thread_loop != 0) */

  return ((void *) 0);
}