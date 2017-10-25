static void close_one(struct connectdata *conn,
                      int index)
{
  if(conn->ssl[index].session) {
    gnutls_bye(conn->ssl[index].session, GNUTLS_SHUT_RDWR);
    gnutls_deinit(conn->ssl[index].session);
  }
  gnutls_certificate_free_credentials(conn->ssl[index].cred);
}