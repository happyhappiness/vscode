f(ssl_get_peer_cert(&(connssl->ssl))) {
    /* If the session was resumed, there will be no peer certs */
    memset(buffer, 0, sizeof(buffer));

    if(x509_crt_info(buffer, sizeof(buffer), (char *)"* ",
                     ssl_get_peer_cert(&(connssl->ssl))) != -1)
      infof(data, "Dumping cert info:\n%s\n", buffer);
  }