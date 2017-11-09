static SECStatus BadCertHandler(void *arg, PRFileDesc *sock)
{
  struct connectdata *conn = (struct connectdata *)arg;
  struct Curl_easy *data = conn->data;
  PRErrorCode err = PR_GetError();
  CERTCertificate *cert;

  /* remember the cert verification result */
  if(SSL_IS_PROXY())
    data->set.proxy_ssl.certverifyresult = err;
  else
    data->set.ssl.certverifyresult = err;

  if(err == SSL_ERROR_BAD_CERT_DOMAIN && !SSL_CONN_CONFIG(verifyhost))
    /* we are asked not to verify the host name */
    return SECSuccess;

  /* print only info about the cert, the error is printed off the callback */
  cert = SSL_PeerCertificate(sock);
  if(cert) {
    infof(data, "Server certificate:\n");
    display_cert_info(data, cert);
    CERT_DestroyCertificate(cert);
  }

  return SECFailure;
}