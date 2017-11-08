static SECStatus nss_auth_cert_hook(void *arg, PRFileDesc *fd, PRBool checksig,
                                    PRBool isServer)
{
  struct connectdata *conn = (struct connectdata *)arg;
  if(!conn->data->set.ssl.verifypeer) {
    infof(conn->data, "skipping SSL peer certificate verification\n");
    return SECSuccess;
  }

  return SSL_AuthCertificate(CERT_GetDefaultCertDB(), fd, checksig, isServer);
}