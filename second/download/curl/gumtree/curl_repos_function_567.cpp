static CURLcode ftp_cwd_and_mkd(struct connectdata *conn, char *path)
{
  CURLcode result;

  result = ftp_cwd(conn, path);
  if (result) {
    if(conn->data->set.ftp_create_missing_dirs) {
      result = ftp_mkd(conn, path);
      if (result)
        /* ftp_mkd() calls failf() itself */
        return result;
      result = ftp_cwd(conn, path);
    }
    if(result)
      failf(conn->data, "Couldn't CWD to %s", path);
  }
  return result;
}