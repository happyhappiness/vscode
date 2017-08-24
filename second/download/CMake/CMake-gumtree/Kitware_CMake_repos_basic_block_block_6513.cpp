{
  int n = 0, rc;
  long res;
  unsigned char *certbuf, *der;
  size_t buflen, derlen, offset = 0;

  if(read_cert(cafile, &certbuf, &buflen) < 0) {
    failf(data, "SSL: failed to read or invalid CA certificate");
    return CURLE_SSL_CACERT;
  }

  /*
   * Certbuf now contains the contents of the certificate file, which can be
   * - a single DER certificate,
   * - a single PEM certificate or
   * - a bunch of PEM certificates (certificate bundle).
   *
   * Go through certbuf, and convert any PEM certificate in it into DER
   * format.
   */
  CFMutableArrayRef array = CFArrayCreateMutable(kCFAllocatorDefault, 0,
                                                 &kCFTypeArrayCallBacks);
  if(array == NULL) {
    free(certbuf);
    failf(data, "SSL: out of memory creating CA certificate array");
    return CURLE_OUT_OF_MEMORY;
  }

  while(offset < buflen) {
    n++;

    /*
     * Check if the certificate is in PEM format, and convert it to DER. If
     * this fails, we assume the certificate is in DER format.
     */
    res = pem_to_der((const char *)certbuf + offset, &der, &derlen);
    if(res < 0) {
      free(certbuf);
      CFRelease(array);
      failf(data, "SSL: invalid CA certificate #%d (offset %d) in bundle",
            n, offset);
      return CURLE_SSL_CACERT;
    }
    offset += res;

    if(res == 0 && offset == 0) {
      /* This is not a PEM file, probably a certificate in DER format. */
      rc = append_cert_to_array(data, certbuf, buflen, array);
      free(certbuf);
      if(rc != CURLE_OK) {
        CFRelease(array);
        return rc;
      }
      break;
    }
    else if(res == 0) {
      /* No more certificates in the bundle. */
      free(certbuf);
      break;
    }

    rc = append_cert_to_array(data, der, derlen, array);
    free(der);
    if(rc != CURLE_OK) {
      free(certbuf);
      CFRelease(array);
      return rc;
    }
  }

  SecTrustRef trust;
  OSStatus ret = SSLCopyPeerTrust(ctx, &trust);
  if(trust == NULL) {
    failf(data, "SSL: error getting certificate chain");
    CFRelease(array);
    return CURLE_OUT_OF_MEMORY;
  }
  else if(ret != noErr) {
    CFRelease(array);
    return sslerr_to_curlerr(data, ret);
  }

  ret = SecTrustSetAnchorCertificates(trust, array);
  if(ret != noErr) {
    CFRelease(trust);
    return sslerr_to_curlerr(data, ret);
  }
  ret = SecTrustSetAnchorCertificatesOnly(trust, true);
  if(ret != noErr) {
    CFRelease(trust);
    return sslerr_to_curlerr(data, ret);
  }

  SecTrustResultType trust_eval = 0;
  ret = SecTrustEvaluate(trust, &trust_eval);
  CFRelease(array);
  CFRelease(trust);
  if(ret != noErr) {
    return sslerr_to_curlerr(data, ret);
  }

  switch(trust_eval) {
    case kSecTrustResultUnspecified:
    case kSecTrustResultProceed:
      return CURLE_OK;

    case kSecTrustResultRecoverableTrustFailure:
    case kSecTrustResultDeny:
    default:
      failf(data, "SSL: certificate verification failed (result: %d)",
            trust_eval);
      return CURLE_PEER_FAILED_VERIFICATION;
  }
}