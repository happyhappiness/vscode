static CURLcode ftp_3rdparty_transfer(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  ssize_t nread;
  int ftpcode, ip[4], port[2];
  struct SessionHandle *data = conn->data;
  struct connectdata *sec_conn = conn->sec_conn;
  char *buf = data->state.buffer;   /* this is our buffer */
  char *str = buf;
  char pasv_port[50];
  const char *stor_cmd;
  struct connectdata *pasv_conn;
  struct connectdata *port_conn;

  if (data->set.ftpport == NULL) {
    pasv_conn = conn;
    port_conn = sec_conn;
  }
  else {
    pasv_conn = sec_conn;
    port_conn = conn;
  }

  result = ftp_cwd_and_create_path(conn);
  if (result)
    return result;

  /* sets the passive mode */
  FTPSENDF(pasv_conn, "%s", "PASV");
  result = Curl_GetFTPResponse(&nread, pasv_conn, &ftpcode);
  if (result)
    return result;

  if (ftpcode != 227) {
    failf(data, "Odd return code after PASV: %03d", ftpcode);
    return CURLE_FTP_WEIRD_PASV_REPLY;
  }

  while (*str) {
    if (6 == sscanf(str, "%d,%d,%d,%d,%d,%d",
                    &ip[0], &ip[1], &ip[2], &ip[3], &port[0], &port[1]))
      break;
    str++;
  }

  if (!*str) {
    failf(pasv_conn->data, "Couldn't interpret the 227-reply");
    return CURLE_FTP_WEIRD_227_FORMAT;
  }

  snprintf(pasv_port, sizeof(pasv_port), "%d,%d,%d,%d,%d,%d", ip[0], ip[1],
           ip[2], ip[3], port[0], port[1]);

  /* sets data connection between remote hosts */
  FTPSENDF(port_conn, "PORT %s", pasv_port);
  result = Curl_GetFTPResponse(&nread, port_conn, &ftpcode);
  if (result)
    return result;

  if (ftpcode != 200) {
    failf(data, "PORT command attempts failed: %03d", ftpcode);
    return CURLE_FTP_PORT_FAILED;
  }

  /* we might append onto the file instead of overwriting it */
  stor_cmd = data->set.ftp_append?"APPE":"STOR";

  /* transfers file between remote hosts */
  /* FIX: this should send a series of CWD commands and then RETR only the
     ftp->file file. The conn->path "full path" is not unescaped. Test case
     230 tests this. */
  FTPSENDF(sec_conn, "RETR %s", sec_conn->path);

  if(!data->set.ftpport) {

    result = Curl_GetFTPResponse(&nread, sec_conn, &ftpcode);
    if (result)
      return result;

    if((ftpcode != 150) && (ftpcode != 125)) {
      failf(data, "Failed RETR: %03d", ftpcode);
      return CURLE_FTP_COULDNT_RETR_FILE;
    }

    result = Curl_ftpsendf(conn, "%s %s", stor_cmd, conn->proto.ftp->file);
    if(CURLE_OK == result)
      result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
    if (result)
      return result;

    if (ftpcode >= 400) {
      failf(data, "Failed FTP upload: %03d", ftpcode);
      return CURLE_FTP_COULDNT_STOR_FILE;
    }

  }
  else {

    result = Curl_ftpsendf(conn, "%s %s", stor_cmd, conn->proto.ftp->file);
    if(CURLE_OK == result)
      result = Curl_GetFTPResponse(&nread, sec_conn, &ftpcode);
    if (result)
      return result;

    if (ftpcode >= 400) {
      failf(data, "Failed FTP upload: %03d", ftpcode);
      return CURLE_FTP_COULDNT_STOR_FILE;
    }

    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
    if (result)
      return result;

    if((ftpcode != 150) && (ftpcode != 125)) {
      failf(data, "Failed FTP upload: %03d", ftpcode);
      return CURLE_FTP_COULDNT_STOR_FILE;
    }
  }

  return CURLE_OK;
}