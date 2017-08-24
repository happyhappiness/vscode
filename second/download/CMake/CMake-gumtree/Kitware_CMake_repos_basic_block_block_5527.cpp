{
    gss_send_token.length = 1;
    gss_send_token.value = malloc(1);
    if(!gss_send_token.value) {
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_OUT_OF_MEMORY;
    }
    memcpy(gss_send_token.value, &gss_enc, 1);

    gss_major_status = gss_wrap(&gss_minor_status, gss_context, 0,
                                GSS_C_QOP_DEFAULT, &gss_send_token,
                                &gss_conf_state, &gss_w_token);

    if(check_gss_err(data, gss_major_status, gss_minor_status, "gss_wrap")) {
      gss_release_buffer(&gss_status, &gss_send_token);
      gss_release_buffer(&gss_status, &gss_w_token);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      failf(data, "Failed to wrap GSS-API encryption value into token.");
      return CURLE_COULDNT_CONNECT;
    }
    gss_release_buffer(&gss_status, &gss_send_token);

    us_length = htons((short)gss_w_token.length);
    memcpy(socksreq+2, &us_length, sizeof(short));
  }