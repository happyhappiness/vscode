static int tunnel_socket_close (CONNECTION* conn)
{
  TUNNEL_DATA* tunnel = (TUNNEL_DATA*) conn->sockdata;

  close (tunnel->readfd);
  close (tunnel->writefd);
  waitpid (tunnel->pid, NULL, 0);
  FREE (&conn->sockdata);

  return 0;
}