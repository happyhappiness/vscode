static void close_one(struct connectdata *conn,
                      int idx)
{
  if(conn->ssl[idx].session) {
    gnutls_bye(conn->ssl[idx].session, GNUTLS_SHUT_RDWR);
    gnutls_deinit(conn->ssl[idx].session);
    conn->ssl[idx].session = NULL;
  }
  if(conn->ssl[idx].cred) {
    gnutls_certificate_free_credentials(conn->ssl[idx].cred);
    conn->ssl[idx].cred = NULL;
  }
}