{
    gss_delete_sec_context(&gss_status, &gss_context, NULL);
    gss_release_name(&gss_status, &gss_client_name);
    failf(data, "Failed to determine user name.");
    return CURLE_COULDNT_CONNECT;
  }