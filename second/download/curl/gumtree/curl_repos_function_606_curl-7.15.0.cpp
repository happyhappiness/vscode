static
CURLcode ftp_cwd_and_create_path(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  /* the ftp struct is already inited in Curl_ftp_connect() */
  struct FTP *ftp = conn->proto.ftp;
  int i;

  if(ftp->cwddone)
    /* already done and fine */
    return CURLE_OK;

  /* This is a re-used connection. Since we change directory to where the
     transfer is taking place, we must now get back to the original dir
     where we ended up after login: */
  if (conn->bits.reuse && ftp->entrypath) {
    if ((result = ftp_cwd_and_mkd(conn, ftp->entrypath)) != CURLE_OK)
      return result;
  }

  for (i=0; i < ftp->dirdepth; i++) {
    /* RFC 1738 says empty components should be respected too, but
       that is plain stupid since CWD can't be used with an empty argument */
    if ((result = ftp_cwd_and_mkd(conn, ftp->dirs[i])) != CURLE_OK)
      return result;
  }

  return result;
}