static CURLcode scp_done(struct connectdata *conn, CURLcode status,
                         bool premature)
{
  (void)premature; /* not used */

  if(!status)
    state(conn, SSH_SCP_DONE);

  return ssh_done(conn, status);

}