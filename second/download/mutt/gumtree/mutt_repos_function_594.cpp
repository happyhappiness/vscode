static int tunnel_socket_close (CONNECTION* conn)
{
  TUNNEL_DATA* tunnel = (TUNNEL_DATA*) conn->sockdata;
  int status;

  close (tunnel->readfd);
  close (tunnel->writefd);
  waitpid (tunnel->pid, &status, 0);
  if (!WIFEXITED(status) || WEXITSTATUS(status))
  {
    mutt_error(_("Tunnel to %s returned error %d (%s)"), conn->account.host,
               WEXITSTATUS(status),
               NONULL(mutt_strsysexit(WEXITSTATUS(status))));
    mutt_sleep (2);
  }
  FREE (&conn->sockdata);

  return 0;
}