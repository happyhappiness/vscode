{
    CFDataRef certdata = CFDataCreate(kCFAllocatorDefault, buf, buflen);
    if(!certdata) {
      failf(data, "SSL: failed to allocate array for CA certificate");
      return CURLE_OUT_OF_MEMORY;
    }

    SecCertificateRef cacert =
      SecCertificateCreateWithData(kCFAllocatorDefault, certdata);
    CFRelease(certdata);
    if(!cacert) {
      failf(data, "SSL: failed to create SecCertificate from CA certificate");
      return CURLE_SSL_CACERT;
    }

    /* Check if cacert is valid. */
    CFStringRef subject = CopyCertSubject(cacert);
    if(subject) {
      char subject_cbuf[128];
      memset(subject_cbuf, 0, 128);
      if(!CFStringGetCString(subject,
                            subject_cbuf,
                            128,
                            kCFStringEncodingUTF8)) {
        CFRelease(cacert);
        failf(data, "SSL: invalid CA certificate subject");
        return CURLE_SSL_CACERT;
      }
      CFRelease(subject);
    }
    else {
      CFRelease(cacert);
      failf(data, "SSL: invalid CA certificate");
      return CURLE_SSL_CACERT;
    }

    CFArrayAppendValue(array, cacert);
    CFRelease(cacert);

    return CURLE_OK;
}