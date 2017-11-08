static CURLcode verifystatus(struct connectdata *conn,
                             struct ssl_connect_data *connssl)
{
  int i, ocsp_status;
  const unsigned char *p;
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  OCSP_RESPONSE *rsp = NULL;
  OCSP_BASICRESP *br = NULL;
  X509_STORE     *st = NULL;
  STACK_OF(X509) *ch = NULL;

  long len = SSL_get_tlsext_status_ocsp_resp(connssl->handle, &p);

  if(!p) {
    failf(data, "No OCSP response received");
    result = CURLE_SSL_INVALIDCERTSTATUS;
    goto end;
  }

  rsp = d2i_OCSP_RESPONSE(NULL, &p, len);
  if(!rsp) {
    failf(data, "Invalid OCSP response");
    result = CURLE_SSL_INVALIDCERTSTATUS;
    goto end;
  }

  ocsp_status = OCSP_response_status(rsp);
  if(ocsp_status != OCSP_RESPONSE_STATUS_SUCCESSFUL) {
    failf(data, "Invalid OCSP response status: %s (%d)",
          OCSP_response_status_str(ocsp_status), ocsp_status);
    result = CURLE_SSL_INVALIDCERTSTATUS;
    goto end;
  }

  br = OCSP_response_get1_basic(rsp);
  if(!br) {
    failf(data, "Invalid OCSP response");
    result = CURLE_SSL_INVALIDCERTSTATUS;
    goto end;
  }

  ch = SSL_get_peer_cert_chain(connssl->handle);
  st = SSL_CTX_get_cert_store(connssl->ctx);

  /* The authorized responder cert in the OCSP response MUST be signed by the
     peer cert's issuer (see RFC6960 section 4.2.2.2). If that's a root cert,
     no problem, but if it's an intermediate cert OpenSSL has a bug where it
     expects this issuer to be present in the chain embedded in the OCSP
     response. So we add it if necessary. */

  /* First make sure the peer cert chain includes both a peer and an issuer,
     and the OCSP response contains a responder cert. */
  if(sk_X509_num(ch) >= 2 && sk_X509_num(br->certs) >= 1) {
    X509 *responder = sk_X509_value(br->certs, sk_X509_num(br->certs) - 1);

    /* Find issuer of responder cert and add it to the OCSP response chain */
    for(i = 0; i < sk_X509_num(ch); i++) {
      X509 *issuer = sk_X509_value(ch, i);
      if(X509_check_issued(issuer, responder) == X509_V_OK) {
        if(!OCSP_basic_add1_cert(br, issuer)) {
          failf(data, "Could not add issuer cert to OCSP response");
          result = CURLE_SSL_INVALIDCERTSTATUS;
          goto end;
        }
      }
    }
  }

  if(OCSP_basic_verify(br, ch, st, 0) <= 0) {
    failf(data, "OCSP response verification failed");
    result = CURLE_SSL_INVALIDCERTSTATUS;
    goto end;
  }

  for(i = 0; i < sk_OCSP_SINGLERESP_num(br->tbsResponseData->responses); i++) {
    int cert_status, crl_reason;
    OCSP_SINGLERESP *single = NULL;

    ASN1_GENERALIZEDTIME *rev, *thisupd, *nextupd;

    if(!sk_OCSP_SINGLERESP_value(br->tbsResponseData->responses, i))
      continue;

    single = sk_OCSP_SINGLERESP_value(br->tbsResponseData->responses, i);

    cert_status = OCSP_single_get0_status(single, &crl_reason, &rev,
                                          &thisupd, &nextupd);

    if(!OCSP_check_validity(thisupd, nextupd, 300L, -1L)) {
      failf(data, "OCSP response has expired");
      result = CURLE_SSL_INVALIDCERTSTATUS;
      goto end;
    }

    infof(data, "SSL certificate status: %s (%d)\n",
          OCSP_cert_status_str(cert_status), cert_status);

    switch(cert_status) {
      case V_OCSP_CERTSTATUS_GOOD:
        break;

      case V_OCSP_CERTSTATUS_REVOKED:
        result = CURLE_SSL_INVALIDCERTSTATUS;

        failf(data, "SSL certificate revocation reason: %s (%d)",
              OCSP_crl_reason_str(crl_reason), crl_reason);
        goto end;

      case V_OCSP_CERTSTATUS_UNKNOWN:
        result = CURLE_SSL_INVALIDCERTSTATUS;
        goto end;
    }
  }

end:
  if(br) OCSP_BASICRESP_free(br);
  OCSP_RESPONSE_free(rsp);

  return result;
}