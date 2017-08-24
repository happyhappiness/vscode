f(ssl_connect_3 == connssl->connecting_state) {
    result = polarssl_connect_step3(conn, sockindex);
    if(result)
      return result;
  }