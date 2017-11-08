static CURLcode
darwinssl_connect_step3(struct connectdata *conn,
                        int sockindex)
{
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  CFStringRef server_cert_summary;
  char server_cert_summary_c[128];
  CFArrayRef server_certs = NULL;
  SecCertificateRef server_cert;
  OSStatus err;
  CFIndex i, count;
  SecTrustRef trust = NULL;

  /* There is no step 3!
   * Well, okay, if verbose mode is on, let's print the details of the
   * server certificates. */
#if CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS
#if CURL_BUILD_IOS
#pragma unused(server_certs)
  err = SSLCopyPeerTrust(connssl->ssl_ctx, &trust);
  /* For some reason, SSLCopyPeerTrust() can return noErr and yet return
     a null trust, so be on guard for that: */
  if(err == noErr && trust) {
    count = SecTrustGetCertificateCount(trust);
    for(i = 0L ; i < count ; i++) {
      server_cert = SecTrustGetCertificateAtIndex(trust, i);
      server_cert_summary = CopyCertSubject(server_cert);
      memset(server_cert_summary_c, 0, 128);
      if(CFStringGetCString(server_cert_summary,
                            server_cert_summary_c,
                            128,
                            kCFStringEncodingUTF8)) {
        infof(data, "Server certificate: %s\n", server_cert_summary_c);
      }
      CFRelease(server_cert_summary);
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
    err = SSLCopyPeerTrust(connssl->ssl_ctx, &trust);
    /* For some reason, SSLCopyPeerTrust() can return noErr and yet return
       a null trust, so be on guard for that: */
    if(err == noErr && trust) {
      count = SecTrustGetCertificateCount(trust);
      for(i = 0L ; i < count ; i++) {
        server_cert = SecTrustGetCertificateAtIndex(trust, i);
        server_cert_summary = CopyCertSubject(server_cert);
        memset(server_cert_summary_c, 0, 128);
        if(CFStringGetCString(server_cert_summary,
                              server_cert_summary_c,
                              128,
                              kCFStringEncodingUTF8)) {
          infof(data, "Server certificate: %s\n", server_cert_summary_c);
        }
        CFRelease(server_cert_summary);
      }
      CFRelease(trust);
    }
  }
  else {
#if CURL_SUPPORT_MAC_10_8
    err = SSLCopyPeerCertificates(connssl->ssl_ctx, &server_certs);
    /* Just in case SSLCopyPeerCertificates() returns null too... */
    if(err == noErr && server_certs) {
      count = CFArrayGetCount(server_certs);
      for(i = 0L ; i < count ; i++) {
        server_cert = (SecCertificateRef)CFArrayGetValueAtIndex(server_certs,
                                                                i);

        server_cert_summary = CopyCertSubject(server_cert);
        memset(server_cert_summary_c, 0, 128);
        if(CFStringGetCString(server_cert_summary,
                              server_cert_summary_c,
                              128,
                              kCFStringEncodingUTF8)) {
          infof(data, "Server certificate: %s\n", server_cert_summary_c);
        }
        CFRelease(server_cert_summary);
      }
      CFRelease(server_certs);
    }
#endif /* CURL_SUPPORT_MAC_10_8 */
  }
#endif /* CURL_BUILD_IOS */
#else
#pragma unused(trust)
  err = SSLCopyPeerCertificates(connssl->ssl_ctx, &server_certs);
  if(err == noErr) {
    count = CFArrayGetCount(server_certs);
    for(i = 0L ; i < count ; i++) {
      server_cert = (SecCertificateRef)CFArrayGetValueAtIndex(server_certs, i);
      server_cert_summary = CopyCertSubject(server_cert);
      memset(server_cert_summary_c, 0, 128);
      if(CFStringGetCString(server_cert_summary,
                            server_cert_summary_c,
                            128,
                            kCFStringEncodingUTF8)) {
        infof(data, "Server certificate: %s\n", server_cert_summary_c);
      }
      CFRelease(server_cert_summary);
    }
    CFRelease(server_certs);
  }
#endif /* CURL_BUILD_MAC_10_7 || CURL_BUILD_IOS */

  connssl->connecting_state = ssl_connect_done;
  return CURLE_OK;
}