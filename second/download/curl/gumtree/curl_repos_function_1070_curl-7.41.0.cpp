static CURLcode scp_doing(struct connectdata *conn,
                               bool *dophase_done)
{
  CURLcode result;
  result = ssh_multi_statemach(conn, dophase_done);

  if(*dophase_done) {
    DEBUGF(infof(conn->data, "DO phase is complete\n"));
  }
  return result;
}