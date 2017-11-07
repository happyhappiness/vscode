static int tls_socket_close (CONNECTION* conn)
{
  tlssockdata *data = conn->sockdata;
  if (data)
  {
    /* shut down only the write half to avoid hanging waiting for the remote to respond.
     *
     * RFC5246 7.2.1. "Closure Alerts"
     *
     * It is not required for the initiator of the close to wait for the
     * responding close_notify alert before closing the read side of the
     * connection.
     */
    gnutls_bye (data->state, GNUTLS_SHUT_WR);

    gnutls_certificate_free_credentials (data->xcred);
    gnutls_deinit (data->state);
    FREE (&conn->sockdata);
  }

  return raw_socket_close (conn);
}