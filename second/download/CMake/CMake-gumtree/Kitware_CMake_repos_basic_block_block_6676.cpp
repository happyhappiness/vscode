f(addrlen) {
      for(i=0; ; i++) {
        certaddrlen = sizeof(certaddr);
        ret = gnutls_x509_crt_get_subject_alt_name(x509_cert, i, certaddr,
                                                   &certaddrlen, NULL);
        /* If this happens, it wasn't an IP address. */
        if(ret == GNUTLS_E_SHORT_MEMORY_BUFFER)
          continue;
        if(ret < 0)
          break;
        if(ret != GNUTLS_SAN_IPADDRESS)
          continue;
        if(certaddrlen == addrlen && !memcmp(addrbuf, certaddr, addrlen)) {
          rc = 1;
          break;
        }
      }
    }