static CURLcode scp_done(struct connectdata *conn, CURLcode status,
                         bool premature)
{
  (void)premature; /* not used */

  if(status == CURLE_OK)
    state(conn, SSH_SCP_DONE);

  return ssh_done(conn, status);

}