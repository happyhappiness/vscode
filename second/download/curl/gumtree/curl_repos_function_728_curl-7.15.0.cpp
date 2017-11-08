CURLcode Curl_is_resolved(struct connectdata *conn,
                          struct Curl_dns_entry **dns)
{
  fd_set read_fds, write_fds;
  struct timeval tv={0,0};
  struct SessionHandle *data = conn->data;
  int nfds;

  FD_ZERO(&read_fds);
  FD_ZERO(&write_fds);

  nfds = ares_fds(data->state.areschannel, &read_fds, &write_fds);

  (void)select(nfds, &read_fds, &write_fds, NULL,
               (struct timeval *)&tv);

  /* Call ares_process() unconditonally here, even if we simply timed out
     above, as otherwise the ares name resolve won't timeout! */
  ares_process(data->state.areschannel, &read_fds, &write_fds);

  *dns = NULL;

  if(conn->async.done) {
    /* we're done, kill the ares handle */
    if(!conn->async.dns) {
      failf(data, "Could not resolve host: %s (%s)", conn->host.dispname,
            ares_strerror(conn->async.status));
      return CURLE_COULDNT_RESOLVE_HOST;
    }
    *dns = conn->async.dns;
  }

  return CURLE_OK;
}