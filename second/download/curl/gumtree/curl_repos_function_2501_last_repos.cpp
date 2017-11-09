static void
show_verbose_server_cert(struct connectdata *conn,
                         int sockindex)
{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  CFArrayRef server_certs = NULL;
  SecCertificateRef server_cert;
  OSStatus err;
  CFIndex i, count;
  SecTrustRef trust = NULL;

  if(!BACKEND->ssl_ctx)
    return;

#if CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS
#if CURL_BUILD_IOS
#pragma unused(server_certs)
  err = SSLCopyPeerTrust(BACKEND->ssl_ctx, &trust);
  /* For some reason, SSLCopyPeerTrust() can return noErr and yet return
     a null trust, so be on guard for that: */
  if(err == noErr && trust) {
    count = SecTrustGetCertificateCount(trust);
    for(i = 0L ; i < count ; i++) {
      CURLcode result;
      char *certp;
      server_cert = SecTrustGetCertificateAtIndex(trust, i);
      result = CopyCertSubject(data, server_cert, &certp);
      if(!result) {
        infof(data, "Server certificate: %s\n", certp);
        free(certp);
      }
    }
    CFRelease(trust);
  }
#else
  /* SSLCopyPeerCertificates() is deprecated as of Mountain Lion.
     The function SecTrustGetCertificateAtIndex() is officially present
     in Lion, but it is unfortunately also present in Snow Leopard as
     private API and doesn't work as expected. So we have to look for
     a different symbol to make sure this code is only executed under
     Lion or later. */
  if(SecTrustEvaluateAsync != NULL) {
#pragma unused(server_certs)
    err = SSLCopyPeerTrust(BACKEND->ssl_ctx, &trust);
    /* For some reason, SSLCopyPeerTrust() can return noErr and yet return
       a null trust, so be on guard for that: */
    if(err == noErr && trust) {
      count = SecTrustGetCertificateCount(trust);
      for(i = 0L ; i < count ; i++) {
        char *certp;
        CURLcode result;
        server_cert = SecTrustGetCertificateAtIndex(trust, i);
        result = CopyCertSubject(data, server_cert, &certp);
        if(!result) {
          infof(data, "Server certificate: %s\n", certp);
          free(certp);
        }
      }
      CFRelease(trust);
    }
  }
  else {
#if CURL_SUPPORT_MAC_10_8
    err = SSLCopyPeerCertificates(BACKEND->ssl_ctx, &server_certs);
    /* Just in case SSLCopyPeerCertificates() returns null too... */
    if(err == noErr && server_certs) {
      count = CFArrayGetCount(server_certs);
      for(i = 0L ; i < count ; i++) {
        char *certp;
        CURLcode result;
        server_cert = (SecCertificateRef)CFArrayGetValueAtIndex(server_certs,
                                                                i);
        result = CopyCertSubject(data, server_cert, &certp);
        if(!result) {
          infof(data, "Server certificate: %s\n", certp);
          free(certp);
        }
      }
      CFRelease(server_certs);
    }
#endif /* CURL_SUPPORT_MAC_10_8 */
  }
#endif /* CURL_BUILD_IOS */
#else
#pragma unused(trust)
  err = SSLCopyPeerCertificates(BACKEND->ssl_ctx, &server_certs);
  if(err == noErr) {
    count = CFArrayGetCount(server_certs);
    for(i = 0L ; i < count ; i++) {
      CURLcode result;
      char *certp;
      server_cert = (SecCertificateRef)CFArrayGetValueAtIndex(server_certs, i);
      result = CopyCertSubject(data, server_cert, &certp);
      if(!result) {
        infof(data, "Server certificate: %s\n", certp);
        free(certp);
      }
    }
    CFRelease(server_certs);
  }
#endif /* CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS */
}