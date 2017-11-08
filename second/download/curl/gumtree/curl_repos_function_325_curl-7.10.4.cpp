static 
CURLcode ftp_cwd(struct connectdata *conn, char *path)
{
  ssize_t nread;
  int     ftpcode;
  CURLcode result;
  
  FTPSENDF(conn, "CWD %s", path);
  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
  if (result)
    return result;

  if (ftpcode != 250) {
    failf(conn->data, "Couldn't cd to %s", path);
    return CURLE_FTP_ACCESS_DENIED;
  }

  return CURLE_OK;
}