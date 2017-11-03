static void ssl_err (sslsockdata *data, int err)
{
  const char* errmsg;
  unsigned long sslerr;

  switch (SSL_get_error (data->ssl, err))
  {
  case SSL_ERROR_NONE:
    return;
  case SSL_ERROR_ZERO_RETURN:
    errmsg = "SSL connection closed";
    data->isopen = 0;
    break;
  case SSL_ERROR_WANT_READ:
    errmsg = "retry read";
    break;
  case SSL_ERROR_WANT_WRITE:
    errmsg = "retry write";
    break;
  case SSL_ERROR_WANT_CONNECT:
    errmsg = "retry connect";
    break;
  case SSL_ERROR_WANT_ACCEPT:
    errmsg = "retry accept";
    break;
  case SSL_ERROR_WANT_X509_LOOKUP:
    errmsg = "retry x509 lookup";
    break;
  case SSL_ERROR_SYSCALL:
    errmsg = "I/O error";
    data->isopen = 0;
    break;
  case SSL_ERROR_SSL:
    sslerr = ERR_get_error ();
    switch (sslerr)
    {
    case 0:
      switch (err)
      {
      case 0:
	errmsg = "EOF";
	break;
      default:
	errmsg = strerror(errno);
      }
      break;
    default:
      errmsg = ERR_error_string (sslerr, NULL);
    }
    break;
  default:
    errmsg = "unknown error";
  }

  dprint (1, (debugfile, "SSL error: %s\n", errmsg));
}