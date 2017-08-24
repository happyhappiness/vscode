{
    failf(data, "Failed to receive GSS-API encryption response.");
    gss_delete_sec_context(&gss_status, &gss_context, NULL);
    return CURLE_COULDNT_CONNECT;
  }