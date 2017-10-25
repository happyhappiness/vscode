static CURLcode ftp_mkd(struct connectdata *conn, char *path)
{
  CURLcode result=CURLE_OK;
  int ftpcode; /* for ftp status */
  ssize_t nread;

  /* Create a directory on the remote server */
  FTPSENDF(conn, "MKD %s", path);

  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
  if(result)
    return result;

  switch(ftpcode) {
  case 257:
    /* success! */
    infof( conn->data , "Created remote directory %s\n" , path );
    break;
  case 550:
    failf(conn->data, "Permission denied to make directory %s", path);
    result = CURLE_FTP_ACCESS_DENIED;
    break;
  default:
    failf(conn->data, "unrecognized MKD response: %d", ftpcode );
    result = CURLE_FTP_ACCESS_DENIED;
    break;
  }
  return  result;
}