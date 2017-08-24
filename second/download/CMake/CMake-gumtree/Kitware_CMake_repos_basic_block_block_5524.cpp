{
    failf(data, "Failed to send GSS-API encryption request.");
    gss_release_buffer(&gss_status, &gss_w_token);
    gss_delete_sec_context(&gss_status, &gss_context, NULL);
    return CURLE_COULDNT_CONNECT;
  }