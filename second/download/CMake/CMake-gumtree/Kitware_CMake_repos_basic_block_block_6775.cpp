f(key_file)
      result = nss_load_key(conn, sockindex, key_file);
    else
      /* In case the cert file also has the key */
      result = nss_load_key(conn, sockindex, cert_file)