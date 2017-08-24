{
    if(gss_recv_token.length != 1) {
      failf(data, "Invalid GSS-API encryption response length (%d).",
            gss_recv_token.length);
      gss_release_buffer(&gss_status, &gss_recv_token);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }

    memcpy(socksreq, gss_recv_token.value, gss_recv_token.length);
    gss_release_buffer(&gss_status, &gss_recv_token);
  }