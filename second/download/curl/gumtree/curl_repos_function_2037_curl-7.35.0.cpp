static CURLcode gskit_connect_step3(struct connectdata *conn, int sockindex)
{
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  const gsk_cert_data_elem *cdev;
  int cdec;
  const gsk_cert_data_elem *p;
  const char *cert = (const char *) NULL;
  const char *certend;
  int i;
  CURLcode cc;

  /* SSL handshake done: gather certificate info and verify host. */

  if(gskit_status(data, gsk_attribute_get_cert_info(connssl->handle,
                                                    GSK_PARTNER_CERT_INFO,
                                                    &cdev, &cdec),
                  "gsk_attribute_get_cert_info()", CURLE_SSL_CONNECT_ERROR) ==
     CURLE_OK) {
    infof(data, "Server certificate:\n");
    p = cdev;
    for(i = 0; i++ < cdec; p++)
      switch (p->cert_data_id) {
      case CERT_BODY_DER:
        cert = p->cert_data_p;
        certend = cert + cdev->cert_data_l;
        break;
      case CERT_DN_PRINTABLE:
        infof(data, "\t subject: %.*s\n", p->cert_data_l, p->cert_data_p);
        break;
      case CERT_ISSUER_DN_PRINTABLE:
        infof(data, "\t issuer: %.*s\n", p->cert_data_l, p->cert_data_p);
        break;
      case CERT_VALID_FROM:
        infof(data, "\t start date: %.*s\n", p->cert_data_l, p->cert_data_p);
        break;
      case CERT_VALID_TO:
        infof(data, "\t expire date: %.*s\n", p->cert_data_l, p->cert_data_p);
        break;
    }
  }

  /* Verify host. */
  cc = Curl_verifyhost(conn, cert, certend);
  if(cc != CURLE_OK)
    return cc;

  /* The only place GSKit can get the whole CA chain is a validation
     callback where no user data pointer is available. Therefore it's not
     possible to copy this chain into our structures for CAINFO.
     However the server certificate may be available, thus we can return
     info about it. */
  if(data->set.ssl.certinfo) {
    if(Curl_ssl_init_certinfo(data, 1))
      return CURLE_OUT_OF_MEMORY;
    if(cert) {
      cc = Curl_extract_certinfo(conn, 0, cert, certend);
      if(cc != CURLE_OK)
        return cc;
    }
  }

  connssl->connecting_state = ssl_connect_done;
  return CURLE_OK;
}