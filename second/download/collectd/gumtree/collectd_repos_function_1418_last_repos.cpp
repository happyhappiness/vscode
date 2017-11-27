static int request_meta_data(const char *host, const char *name) /* {{{ */
{
  Ganglia_metadata_msg msg = {0};
  char buffer[BUFF_SIZE] = {0};
  unsigned int buffer_size;
  XDR xdr;

  msg.id = gmetadata_request;
  msg.Ganglia_metadata_msg_u.grequest.metric_id.host = strdup(host);
  msg.Ganglia_metadata_msg_u.grequest.metric_id.name = strdup(name);

  if ((msg.Ganglia_metadata_msg_u.grequest.metric_id.host == NULL) ||
      (msg.Ganglia_metadata_msg_u.grequest.metric_id.name == NULL)) {
    sfree(msg.Ganglia_metadata_msg_u.grequest.metric_id.host);
    sfree(msg.Ganglia_metadata_msg_u.grequest.metric_id.name);
    return -1;
  }

  xdrmem_create(&xdr, buffer, sizeof(buffer), XDR_ENCODE);

  if (!xdr_Ganglia_metadata_msg(&xdr, &msg)) {
    sfree(msg.Ganglia_metadata_msg_u.grequest.metric_id.host);
    sfree(msg.Ganglia_metadata_msg_u.grequest.metric_id.name);
    return -1;
  }

  buffer_size = xdr_getpos(&xdr);

  DEBUG("gmond plugin: Requesting meta data for %s/%s.", host, name);

  pthread_mutex_lock(&mc_send_sockets_lock);
  for (size_t i = 0; i < mc_send_sockets_num; i++) {
    ssize_t status =
        sendto(mc_send_sockets[i].fd, buffer, (size_t)buffer_size,
               /* flags = */ 0, (struct sockaddr *)&mc_send_sockets[i].addr,
               mc_send_sockets[i].addrlen);
    if (status == -1) {
      char errbuf[1024];
      ERROR("gmond plugin: sendto(2) failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      continue;
    }
  }
  pthread_mutex_unlock(&mc_send_sockets_lock);

  sfree(msg.Ganglia_metadata_msg_u.grequest.metric_id.host);
  sfree(msg.Ganglia_metadata_msg_u.grequest.metric_id.name);
  return 0;
}