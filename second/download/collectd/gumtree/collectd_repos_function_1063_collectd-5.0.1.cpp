static int request_meta_data (const char *host, const char *name) /* {{{ */
{
  Ganglia_metadata_msg msg;
  char buffer[BUFF_SIZE];
  unsigned int buffer_size;
  XDR xdr;
  size_t i;

  memset (&msg, 0, sizeof (msg));

  msg.id = gmetadata_request;
  msg.Ganglia_metadata_msg_u.grequest.metric_id.host = strdup (host);
  msg.Ganglia_metadata_msg_u.grequest.metric_id.name = strdup (name);

  if ((msg.Ganglia_metadata_msg_u.grequest.metric_id.host == NULL)
      || (msg.Ganglia_metadata_msg_u.grequest.metric_id.name == NULL))
  {
    sfree (msg.Ganglia_metadata_msg_u.grequest.metric_id.host);
    sfree (msg.Ganglia_metadata_msg_u.grequest.metric_id.name);
    return (-1);
  }

  memset (buffer, 0, sizeof (buffer));
  xdrmem_create (&xdr, buffer, sizeof (buffer), XDR_ENCODE);

  if (!xdr_Ganglia_metadata_msg (&xdr, &msg))
  {
    sfree (msg.Ganglia_metadata_msg_u.grequest.metric_id.host);
    sfree (msg.Ganglia_metadata_msg_u.grequest.metric_id.name);
    return (-1);
  }

  buffer_size = xdr_getpos (&xdr);

  DEBUG ("gmond plugin: Requesting meta data for %s/%s.",
      host, name);

  pthread_mutex_lock (&mc_send_sockets_lock);
  for (i = 0; i < mc_send_sockets_num; i++)
    sendto (mc_send_sockets[i].fd, buffer, (size_t) buffer_size,
        /* flags = */ 0,
        (struct sockaddr *) &mc_send_sockets[i].addr,
        mc_send_sockets[i].addrlen);
  pthread_mutex_unlock (&mc_send_sockets_lock);

  sfree (msg.Ganglia_metadata_msg_u.grequest.metric_id.host);
  sfree (msg.Ganglia_metadata_msg_u.grequest.metric_id.name);
  return (0);
}