static 
CURLcode _ftp_cwd(struct connectdata *conn, char *path)
{
  ssize_t nread;
  int     ftpcode;
  
  ftpsendf(conn->firstsocket, conn, "CWD %s", path);
  nread = Curl_GetFTPResponse(conn->firstsocket, 
                              conn->data->state.buffer, conn, &ftpcode);
  if (nread < 0)
    return CURLE_OPERATION_TIMEOUTED;

  if (ftpcode != 250) {
    failf(conn->data, "Couldn't cd to %s", path);
    return CURLE_FTP_ACCESS_DENIED;
  }

  return CURLE_OK;
}