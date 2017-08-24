{
    gss_major_status = Curl_gss_init_sec_context(data,
                                                 &gss_minor_status,
                                                 &gss_context,
                                                 server,
                                                 &Curl_krb5_mech_oid,
                                                 NULL,
                                                 gss_token,
                                                 &gss_send_token,
                                                 TRUE,
                                                 &gss_ret_flags);

    if(gss_token != GSS_C_NO_BUFFER)
      gss_release_buffer(&gss_status, &gss_recv_token);
    if(check_gss_err(data, gss_major_status,
                     gss_minor_status, "gss_init_sec_context")) {
      gss_release_name(&gss_status, &server);
      gss_release_buffer(&gss_status, &gss_recv_token);
      gss_release_buffer(&gss_status, &gss_send_token);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      failf(data, "Failed to initial GSS-API token.");
      return CURLE_COULDNT_CONNECT;
    }

    if(gss_send_token.length != 0) {
      socksreq[0] = 1;    /* GSS-API subnegotiation version */
      socksreq[1] = 1;    /* authentication message type */
      us_length = htons((short)gss_send_token.length);
      memcpy(socksreq+2, &us_length, sizeof(short));

      code = Curl_write_plain(conn, sock, (char *)socksreq, 4, &written);
      if(code || (4 != written)) {
        failf(data, "Failed to send GSS-API authentication request.");
        gss_release_name(&gss_status, &server);
        gss_release_buffer(&gss_status, &gss_recv_token);
        gss_release_buffer(&gss_status, &gss_send_token);
        gss_delete_sec_context(&gss_status, &gss_context, NULL);
        return CURLE_COULDNT_CONNECT;
      }

      code = Curl_write_plain(conn, sock, (char *)gss_send_token.value,
                              gss_send_token.length, &written);

      if(code || ((ssize_t)gss_send_token.length != written)) {
        failf(data, "Failed to send GSS-API authentication token.");
        gss_release_name(&gss_status, &server);
        gss_release_buffer(&gss_status, &gss_recv_token);
        gss_release_buffer(&gss_status, &gss_send_token);
        gss_delete_sec_context(&gss_status, &gss_context, NULL);
        return CURLE_COULDNT_CONNECT;
      }

    }

    gss_release_buffer(&gss_status, &gss_send_token);
    gss_release_buffer(&gss_status, &gss_recv_token);
    if(gss_major_status != GSS_S_CONTINUE_NEEDED) break;

    /* analyse response */

    /*   GSS-API response looks like
     * +----+------+-----+----------------+
     * |VER | MTYP | LEN |     TOKEN      |
     * +----+------+----------------------+
     * | 1  |  1   |  2  | up to 2^16 - 1 |
     * +----+------+-----+----------------+
     */

    result=Curl_blockread_all(conn, sock, (char *)socksreq, 4, &actualread);
    if(result || (actualread != 4)) {
      failf(data, "Failed to receive GSS-API authentication response.");
      gss_release_name(&gss_status, &server);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }

    /* ignore the first (VER) byte */
    if(socksreq[1] == 255) { /* status / message type */
      failf(data, "User was rejected by the SOCKS5 server (%d %d).",
            socksreq[0], socksreq[1]);
      gss_release_name(&gss_status, &server);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }

    if(socksreq[1] != 1) { /* status / messgae type */
      failf(data, "Invalid GSS-API authentication response type (%d %d).",
            socksreq[0], socksreq[1]);
      gss_release_name(&gss_status, &server);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }

    memcpy(&us_length, socksreq+2, sizeof(short));
    us_length = ntohs(us_length);

    gss_recv_token.length=us_length;
    gss_recv_token.value=malloc(us_length);
    if(!gss_recv_token.value) {
      failf(data,
            "Could not allocate memory for GSS-API authentication "
            "response token.");
      gss_release_name(&gss_status, &server);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_OUT_OF_MEMORY;
    }

    result=Curl_blockread_all(conn, sock, (char *)gss_recv_token.value,
                              gss_recv_token.length, &actualread);

    if(result || (actualread != us_length)) {
      failf(data, "Failed to receive GSS-API authentication token.");
      gss_release_name(&gss_status, &server);
      gss_release_buffer(&gss_status, &gss_recv_token);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }

    gss_token = &gss_recv_token;
  }