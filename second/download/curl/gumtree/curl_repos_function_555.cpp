static CURLcode ftp_transfertype(struct connectdata *conn,
                                  bool ascii)
{
  struct SessionHandle *data = conn->data;
  int ftpcode;
  ssize_t nread;
  CURLcode result;

  FTPSENDF(conn, "TYPE %s", ascii?"A":"I");

  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
  if(result)
    return result;

  if(ftpcode != 200) {
    failf(data, "Couldn't set %s mode",
          ascii?"ASCII":"binary");
    return ascii? CURLE_FTP_COULDNT_SET_ASCII:CURLE_FTP_COULDNT_SET_BINARY;
  }

  return CURLE_OK;
}