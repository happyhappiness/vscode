static
CURLcode ftp_getsize(struct connectdata *conn, char *file,
                      ssize_t *size)
{
  struct SessionHandle *data = conn->data;
  int ftpcode;
  ssize_t nread;
  char *buf=data->state.buffer;
  CURLcode result;

  FTPSENDF(conn, "SIZE %s", file);
  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
  if(result)
    return result;

  if(ftpcode == 213) {
    /* get the size from the ascii string: */
    *size = atoi(buf+4);
  }
  else
    return CURLE_FTP_COULDNT_GET_SIZE;

  return CURLE_OK;
}