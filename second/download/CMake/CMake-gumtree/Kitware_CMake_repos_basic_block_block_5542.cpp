f(gss_send_token.length != 0) {
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