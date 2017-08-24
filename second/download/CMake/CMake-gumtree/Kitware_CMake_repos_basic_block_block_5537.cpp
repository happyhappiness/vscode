f(socksreq[1] == 255) { /* status / message type */
      failf(data, "User was rejected by the SOCKS5 server (%d %d).",
            socksreq[0], socksreq[1]);
      gss_release_name(&gss_status, &server);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }