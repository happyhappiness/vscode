static CURLcode ftp_epsv_disable(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  if(conn->bits.ipv6) {
    /* We can't disable EPSV when doing IPv6, so this is instead a fail */
    failf(conn->data, "Failed EPSV attempt, exiting\n");
    return CURLE_FTP_WEIRD_SERVER_REPLY;
  }

  infof(conn->data, "Failed EPSV attempt. Disabling EPSV\n");
  /* disable it for next transfer */
  conn->bits.ftp_use_epsv = FALSE;
  conn->data->state.errorbuf = FALSE; /* allow error message to get
                                         rewritten */
  PPSENDF(&conn->proto.ftpc.pp, "%s", "PASV");
  conn->proto.ftpc.count1++;
  /* remain in/go to the FTP_PASV state */
  state(conn, FTP_PASV);
  return result;
}