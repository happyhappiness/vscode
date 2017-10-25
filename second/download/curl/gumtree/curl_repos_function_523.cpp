static CURLcode ftp_state_cwd(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->proto.ftp;

  if(ftp->cwddone)
    /* already done and fine */
    result = ftp_state_post_cwd(conn);
  else {
    ftp->count2 = 0;
    if (conn->bits.reuse && ftp->entrypath) {
      /* This is a re-used connection. Since we change directory to where the
         transfer is taking place, we must first get back to the original dir
         where we ended up after login: */
      ftp->count1 = 0; /* we count this as the first path, then we add one
                          for all upcoming ones in the ftp->dirs[] array */
      NBFTPSENDF(conn, "CWD %s", ftp->entrypath);
      state(conn, FTP_CWD);
    }
    else {
      if(ftp->dirdepth) {
        ftp->count1 = 1;
        /* issue the first CWD, the rest is sent when the CWD responses are
           received... */
        NBFTPSENDF(conn, "CWD %s", ftp->dirs[ftp->count1 -1]);
        state(conn, FTP_CWD);
      }
      else {
        /* No CWD necessary */
        result = ftp_state_post_cwd(conn);
      }
    }
  }
  return result;
}