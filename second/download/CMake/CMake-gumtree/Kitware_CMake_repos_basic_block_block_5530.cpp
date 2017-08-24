{
    gss_delete_sec_context(&gss_status, &gss_context, NULL);
    gss_release_name(&gss_status, &gss_client_name);
    gss_release_buffer(&gss_status, &gss_send_token);
    return CURLE_OUT_OF_MEMORY;
  }