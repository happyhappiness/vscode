static int
mutt_nss_socket_close (CONNECTION * con)
{
  mutt_nss_t *sockdata = (mutt_nss_t *) con->sockdata;

  if (PR_Close (sockdata->fd) == PR_FAILURE)
    return -1;

  if (sockdata->db)
    CERT_ClosePermCertDB (sockdata->db);
  /* free up the memory we used for this connection specific to NSS. */
  safe_free ((void **) &con->sockdata);
  return 0;
}