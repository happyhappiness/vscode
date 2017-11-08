static CURLcode map_error_to_curl(int axtls_err)
{
  switch (axtls_err) {
  case SSL_ERROR_NOT_SUPPORTED:
  case SSL_ERROR_INVALID_VERSION:
  case -70:                       /* protocol version alert from server */
    return CURLE_UNSUPPORTED_PROTOCOL;
    break;
  case SSL_ERROR_NO_CIPHER:
    return CURLE_SSL_CIPHER;
    break;
  case SSL_ERROR_BAD_CERTIFICATE: /* this may be bad server cert too */
  case SSL_ERROR_NO_CERT_DEFINED:
  case -42:                       /* bad certificate alert from server */
  case -43:                       /* unsupported cert alert from server */
  case -44:                       /* cert revoked alert from server */
  case -45:                       /* cert expired alert from server */
  case -46:                       /* cert unknown alert from server */
    return CURLE_SSL_CERTPROBLEM;
    break;
  case SSL_X509_ERROR(X509_NOT_OK):
  case SSL_X509_ERROR(X509_VFY_ERROR_NO_TRUSTED_CERT):
  case SSL_X509_ERROR(X509_VFY_ERROR_BAD_SIGNATURE):
  case SSL_X509_ERROR(X509_VFY_ERROR_NOT_YET_VALID):
  case SSL_X509_ERROR(X509_VFY_ERROR_EXPIRED):
  case SSL_X509_ERROR(X509_VFY_ERROR_SELF_SIGNED):
  case SSL_X509_ERROR(X509_VFY_ERROR_INVALID_CHAIN):
  case SSL_X509_ERROR(X509_VFY_ERROR_UNSUPPORTED_DIGEST):
  case SSL_X509_ERROR(X509_INVALID_PRIV_KEY):
    return CURLE_PEER_FAILED_VERIFICATION;
    break;
  case -48:                       /* unknown ca alert from server */
    return CURLE_SSL_CACERT;
    break;
  case -49:                       /* access denied alert from server */
    return CURLE_REMOTE_ACCESS_DENIED;
    break;
  case SSL_ERROR_CONN_LOST:
  case SSL_ERROR_SOCK_SETUP_FAILURE:
  case SSL_ERROR_INVALID_HANDSHAKE:
  case SSL_ERROR_INVALID_PROT_MSG:
  case SSL_ERROR_INVALID_HMAC:
  case SSL_ERROR_INVALID_SESSION:
  case SSL_ERROR_INVALID_KEY:     /* it's too bad this doesn't map better */
  case SSL_ERROR_FINISHED_INVALID:
  case SSL_ERROR_NO_CLIENT_RENOG:
  default:
    return CURLE_SSL_CONNECT_ERROR;
    break;
  }
}