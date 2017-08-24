f(is_cert_file) {
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
      err = CopyIdentityWithLabel(ssl_cert, &cert_and_key)