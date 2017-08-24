{
    result = nss_setup_connect(conn, sockindex);
    if(result)
      /* we do not expect CURLE_AGAIN from nss_setup_connect() */
      return result;

    connssl->connecting_state = ssl_connect_2;
  }