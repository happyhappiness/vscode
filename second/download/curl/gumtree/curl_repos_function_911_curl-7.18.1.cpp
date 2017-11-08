static CURLcode ftp_doing(struct connectdata *conn,
                               bool *dophase_done)
{
  CURLcode result;
  result = ftp_multi_statemach(conn, dophase_done);

  if(*dophase_done) {
    result = ftp_dophase_done(conn, FALSE /* not connected */);

    DEBUGF(infof(conn->data, "DO phase is complete\n"));
  }
  return result;
}