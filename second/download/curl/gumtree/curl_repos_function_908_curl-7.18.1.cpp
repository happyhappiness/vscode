static CURLcode ftp_disconnect(struct connectdata *conn)
{
  struct ftp_conn *ftpc= &conn->proto.ftpc;

  /* We cannot send quit unconditionally. If this connection is stale or
     bad in any way, sending quit and waiting around here will make the
     disconnect wait in vain and cause more problems than we need to.

     ftp_quit() will check the state of ftp->ctl_valid. If it's ok it
     will try to send the QUIT command, otherwise it will just return.
  */

  /* The FTP session may or may not have been allocated/setup at this point! */
  (void)ftp_quit(conn); /* ignore errors on the QUIT */

  if(ftpc->entrypath) {
    struct SessionHandle *data = conn->data;
    if(data->state.most_recent_ftp_entrypath == ftpc->entrypath) {
      data->state.most_recent_ftp_entrypath = NULL;
    }
    free(ftpc->entrypath);
    ftpc->entrypath = NULL;
  }
  if(ftpc->cache) {
    free(ftpc->cache);
    ftpc->cache = NULL;
  }
  freedirs(ftpc);
  if(ftpc->prevpath) {
    free(ftpc->prevpath);
    ftpc->prevpath = NULL;
  }

  return CURLE_OK;
}