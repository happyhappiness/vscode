static
CURLcode scp_perform(struct connectdata *conn,
                      bool *connected,
                      bool *dophase_done)
{
  CURLcode result = CURLE_OK;

  DEBUGF(infof(conn->data, "DO phase starts\n"));

  *dophase_done = FALSE; /* not done yet */

  /* start the first command in the DO phase */
  state(conn, SSH_SCP_TRANS_INIT);

  /* run the state-machine */
  result = ssh_multi_statemach(conn, dophase_done);

  *connected = conn->bits.tcpconnect[FIRSTSOCKET];

  if(*dophase_done) {
    DEBUGF(infof(conn->data, "DO phase is complete\n"));
  }

  return result;
}