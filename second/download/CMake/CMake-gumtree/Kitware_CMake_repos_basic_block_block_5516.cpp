{
    failf(data, "Failed to receive GSS-API encryptrion type.");
    gss_release_buffer(&gss_status, &gss_recv_token);
    gss_delete_sec_context(&gss_status, &gss_context, NULL);
    return CURLE_COULDNT_CONNECT;
  }