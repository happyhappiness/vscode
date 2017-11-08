static CURLcode _ftp_transfertype(struct connectdata *conn,
                                  bool ascii)
{
  struct SessionHandle *data = conn->data;
  int ftpcode;
  ssize_t nread;
  char *buf=data->state.buffer;

  ftpsendf(conn->firstsocket, conn, "TYPE %s", ascii?"A":"I");

  nread = Curl_GetFTPResponse(conn->firstsocket, buf, conn, &ftpcode);
  if(nread < 0)
    return CURLE_OPERATION_TIMEOUTED;
  
  if(ftpcode != 200) {
    failf(data, "Couldn't set %s mode",
          ascii?"ASCII":"binary");
    return ascii? CURLE_FTP_COULDNT_SET_ASCII:CURLE_FTP_COULDNT_SET_BINARY;
  }

  return CURLE_OK;
}