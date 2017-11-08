static
CURLcode _ftp_getsize(struct connectdata *conn, char *file,
                      ssize_t *size)
{
  struct SessionHandle *data = conn->data;
  int ftpcode;
  ssize_t nread;
  char *buf=data->state.buffer;

  ftpsendf(conn->firstsocket, conn, "SIZE %s", file);
  nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
  if(nread < 0)
    return CURLE_OPERATION_TIMEOUTED;

  if(ftpcode == 213) {
    /* get the size from the ascii string: */
    *size = atoi(buf+4);
  }
  else
    return CURLE_FTP_COULDNT_GET_SIZE;

  return CURLE_OK;
}