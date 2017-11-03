static int tunnel_socket_read (CONNECTION* conn, char* buf, size_t len)
{
  TUNNEL_DATA* tunnel = (TUNNEL_DATA*) conn->sockdata;
  int rc;

  rc = read (tunnel->readfd, buf, len);
  if (rc == -1)
  {
    mutt_error (_("Tunnel error talking to %s: %s"), conn->account.host,
		strerror (errno));
    mutt_sleep (1);
  }

  return rc;
}