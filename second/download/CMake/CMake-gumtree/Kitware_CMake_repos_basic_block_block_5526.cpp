{
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_OUT_OF_MEMORY;
    }