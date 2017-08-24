{
      Curl_gss_log_error(data, "gss_import_name() failed: ",
                         major_status, minor_status);

      free(spn);

      return CURLE_OUT_OF_MEMORY;
    }