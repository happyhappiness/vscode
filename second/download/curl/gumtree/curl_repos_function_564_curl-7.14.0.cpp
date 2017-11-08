CURLcode Curl_ftp_disconnect(struct connectdata *conn)
{
  struct FTP *ftp= conn->proto.ftp;

  /* We cannot send quit unconditionally. If this connection is stale or
     bad in any way, sending quit and waiting around here will make the
     disconnect wait in vain and cause more problems than we need to.

     ftp_quit() will check the state of ftp->ctl_valid. If it's ok it
     will try to send the QUIT command, otherwise it will just return.
  */

  /* The FTP session may or may not have been allocated/setup at this point! */
  if(ftp) {
    (void)ftp_quit(conn); /* ignore errors on the QUIT */

    if(ftp->entrypath)
      free(ftp->entrypath);
    if(ftp->cache) {
      free(ftp->cache);
      ftp->cache = NULL;
    }
    freedirs(ftp);
    if(ftp->prevpath) {
      free(ftp->prevpath);
      ftp->prevpath = NULL;
    }
  }
  return CURLE_OK;
}