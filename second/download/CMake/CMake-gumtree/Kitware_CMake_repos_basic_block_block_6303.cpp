{
    Curl_gss_log_error(data, "gss_unwrap() failed: ",
                       major_status, minor_status);

    gss_release_buffer(&unused_status, &username_token);
    free(chlg);

    return CURLE_BAD_CONTENT_ENCODING;
  }