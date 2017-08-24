{
    gss_release_buffer(&unused_status, &username_token);

    return CURLE_OUT_OF_MEMORY;
  }