static CURLcode ftp_disconnect(struct connectdata *conn, bool dead_connection)
{
  struct ftp_conn *ftpc= &conn->proto.ftpc;
  struct pingpong *pp = &ftpc->pp;

  /* We cannot send quit unconditionally. If this connection is stale or
     bad in any way, sending quit and waiting around here will make the
     disconnect wait in vain and cause more problems than we need to.

     ftp_quit() will check the state of ftp->ctl_valid. If it's ok it
     will try to send the QUIT command, otherwise it will just return.
  */
  if(dead_connection)
    ftpc->ctl_valid = FALSE;

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

  freedirs(ftpc);
  if(ftpc->prevpath) {
    free(ftpc->prevpath);
    ftpc->prevpath = NULL;
  }
  if(ftpc->server_os) {
    free(ftpc->server_os);
    ftpc->server_os = NULL;
  }

  Curl_pp_disconnect(pp);

#ifdef HAVE_GSSAPI
  Curl_sec_end(conn);
#endif

  return CURLE_OK;
}