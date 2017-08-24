{
    code = Curl_write_plain(conn, sock, (char *)gss_w_token.value,
                            gss_w_token.length, &written);
    if(code || ((ssize_t)gss_w_token.length != written)) {
      failf(data, "Failed to send GSS-API encryption type.");
      gss_release_buffer(&gss_status, &gss_w_token);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }
    gss_release_buffer(&gss_status, &gss_w_token);
  }