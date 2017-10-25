static
CURLcode ftp_cwd(struct connectdata *conn, char *path)
{
  ssize_t nread;
  int     ftpcode;
  CURLcode result;

  FTPSENDF(conn, "CWD %s", path);
  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
  if (!result) {
    /* According to RFC959, CWD is supposed to return 250 on success, but
       there seem to be non-compliant FTP servers out there that return 200,
       so we accept any '2xy' code here. */
    if (ftpcode/100 != 2)
      result = CURLE_FTP_ACCESS_DENIED;
  }

  return result;
}