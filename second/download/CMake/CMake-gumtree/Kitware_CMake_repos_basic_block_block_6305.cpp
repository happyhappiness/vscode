f(GSS_ERROR(major_status)) {
    Curl_gss_log_error(data, "gss_display_name() failed: ",
                       major_status, minor_status);

    free(chlg);

    return CURLE_OUT_OF_MEMORY;
  }