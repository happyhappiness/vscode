f(ssl_cert) {
    SecIdentityRef cert_and_key = NULL;
    bool is_cert_file = is_file(ssl_cert);

    /* User wants to authenticate with a client cert. Look for it:
       If we detect that this is a file on disk, then let's load it.
       Otherwise, assume that the user wants to use an identity loaded
       from the Keychain. */
    if(is_cert_file) {
      if(!SSL_SET_OPTION(cert_type))
        infof(data, "WARNING: SSL: Certificate type not set, assuming "
                    "PKCS#12 format.\n");
      else if(strncmp(SSL_SET_OPTION(cert_type), "P12",
        strlen(SSL_SET_OPTION(cert_type))) != 0)
        infof(data, "WARNING: SSL: The Security framework only supports "
                    "loading identities that are in PKCS#12 format.\n");

      err = CopyIdentityFromPKCS12File(ssl_cert,
        SSL_SET_OPTION(key_passwd), &cert_and_key);
    }
    else
      err = CopyIdentityWithLabel(ssl_cert, &cert_and_key);

    if(err == noErr && cert_and_key) {
      SecCertificateRef cert = NULL;
      CFTypeRef certs_c[1];
      CFArrayRef certs;

      /* If we found one, print it out: */
      err = SecIdentityCopyCertificate(cert_and_key, &cert);
      if(err == noErr) {
        CFStringRef cert_summary = CopyCertSubject(cert);
        char cert_summary_c[128];

        if(cert_summary) {
          memset(cert_summary_c, 0, 128);
          if(CFStringGetCString(cert_summary,
                                cert_summary_c,
                                128,
                                kCFStringEncodingUTF8)) {
            infof(data, "Client certificate: %s\n", cert_summary_c);
          }
          CFRelease(cert_summary);
          CFRelease(cert);
        }
      }
      certs_c[0] = cert_and_key;
      certs = CFArrayCreate(NULL, (const void **)certs_c, 1L,
                            &kCFTypeArrayCallBacks);
      err = SSLSetCertificate(connssl->ssl_ctx, certs);
      if(certs)
        CFRelease(certs);
      if(err != noErr) {
        failf(data, "SSL: SSLSetCertificate() failed: OSStatus %d", err);
        return CURLE_SSL_CERTPROBLEM;
      }
      CFRelease(cert_and_key);
    }
    else {
      switch(err) {
      case errSecAuthFailed: case -25264: /* errSecPkcs12VerifyFailure */
        failf(data, "SSL: Incorrect password for the certificate \"%s\" "
                    "and its private key.", ssl_cert);
        break;
      case -26275: /* errSecDecode */ case -25257: /* errSecUnknownFormat */
        failf(data, "SSL: Couldn't make sense of the data in the "
                    "certificate \"%s\" and its private key.",
                    ssl_cert);
        break;
      case -25260: /* errSecPassphraseRequired */
        failf(data, "SSL The certificate \"%s\" requires a password.",
                    ssl_cert);
        break;
      case errSecItemNotFound:
        failf(data, "SSL: Can't find the certificate \"%s\" and its private "
                    "key in the Keychain.", ssl_cert);
        break;
      default:
        failf(data, "SSL: Can't load the certificate \"%s\" and its private "
                    "key: OSStatus %d", ssl_cert, err);
        break;
      }
      return CURLE_SSL_CERTPROBLEM;
    }
  }