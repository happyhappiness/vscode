{
    failf(data, "Failed to create service name.");
    gss_release_name(&gss_status, &server);
    return CURLE_COULDNT_CONNECT;
  }