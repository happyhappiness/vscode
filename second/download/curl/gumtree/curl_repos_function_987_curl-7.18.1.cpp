static SECStatus BadCertHandler(void *arg, PRFileDesc *sock)
{
  SECStatus success = SECSuccess;
  struct connectdata *conn = (struct connectdata *)arg;
  PRErrorCode err = PR_GetError();
  CERTCertificate *cert = NULL;
  char *subject, *issuer;

  if(conn->data->set.ssl.certverifyresult!=0)
    return success;

  conn->data->set.ssl.certverifyresult=err;
  cert = SSL_PeerCertificate(sock);
  subject = CERT_NameToAscii(&cert->subject);
  issuer = CERT_NameToAscii(&cert->issuer);
  CERT_DestroyCertificate(cert);

  switch(err) {
  case SEC_ERROR_CA_CERT_INVALID:
    infof(conn->data, "Issuer certificate is invalid: '%s'\n", issuer);
    if(conn->data->set.ssl.verifypeer)
      success = SECFailure;
    break;
  case SEC_ERROR_UNTRUSTED_ISSUER:
    if(conn->data->set.ssl.verifypeer)
      success = SECFailure;
    infof(conn->data, "Certificate is signed by an untrusted issuer: '%s'\n",
          issuer);
    break;
  case SSL_ERROR_BAD_CERT_DOMAIN:
    if(conn->data->set.ssl.verifypeer)
      success = SECFailure;
    infof(conn->data, "common name: %s (does not match '%s')\n",
          subject, conn->host.dispname);
    break;
  case SEC_ERROR_EXPIRED_CERTIFICATE:
    if(conn->data->set.ssl.verifypeer)
      success = SECFailure;
    infof(conn->data, "Remote Certificate has expired.\n");
    break;
  default:
    if(conn->data->set.ssl.verifypeer)
      success = SECFailure;
    infof(conn->data, "Bad certificate received. Subject = '%s', "
          "Issuer = '%s'\n", subject, issuer);
    break;
  }
  if(success == SECSuccess)
    infof(conn->data, "SSL certificate verify ok.\n");
  PR_Free(subject);
  PR_Free(issuer);

  return success;
}