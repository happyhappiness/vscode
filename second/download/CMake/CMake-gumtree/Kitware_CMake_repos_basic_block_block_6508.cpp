{
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