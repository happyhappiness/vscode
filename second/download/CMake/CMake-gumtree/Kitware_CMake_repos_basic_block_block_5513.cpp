{
      failf(data, "Invalid GSS-API encryption response length (%d).",
            gss_w_token.length);
      gss_release_buffer(&gss_status, &gss_w_token);
      gss_delete_sec_context(&gss_status, &gss_context, NULL);
      return CURLE_COULDNT_CONNECT;
    }