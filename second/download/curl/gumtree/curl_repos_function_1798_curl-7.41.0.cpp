static CURLcode ftp_quit(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  if(conn->proto.ftpc.ctl_valid) {
    result = Curl_pp_sendf(&conn->proto.ftpc.pp, "%s", "QUIT");
    if(result) {
      failf(conn->data, "Failure sending QUIT command: %s",
            curl_easy_strerror(result));
      conn->proto.ftpc.ctl_valid = FALSE; /* mark control connection as bad */
      connclose(conn, "QUIT command failed"); /* mark for connection closure */
      state(conn, FTP_STOP);
      return result;
    }

    state(conn, FTP_QUIT);

    result = ftp_block_statemach(conn);
  }

  return result;
}