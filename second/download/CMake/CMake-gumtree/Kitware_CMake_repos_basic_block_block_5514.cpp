{
    gss_major_status = gss_unwrap(&gss_minor_status, gss_context,
                                  &gss_recv_token, &gss_w_token,
                                  0, GSS_C_QOP_DEFAULT);

    if(check_gss_err(data, gss_major_status, gss_minor_status, "gss_unwrap")) {
      gss_release_buffer(&gss_status, &gss_recv_token);
      gss_release_buffer(&gss_status, &gss_w_token);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      failf(data, "Failed to unwrap GSS-API encryption value into token.");
      return CURLE_COULDNT_CONNECT;
    }
    gss_release_buffer(&gss_status, &gss_recv_token);

    if(gss_w_token.length != 1) {
      failf(data, "Invalid GSS-API encryption response length (%d).",
            gss_w_token.length);
      gss_release_buffer(&gss_status, &gss_w_token);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }

    memcpy(socksreq, gss_w_token.value, gss_w_token.length);
    gss_release_buffer(&gss_status, &gss_w_token);
  }