{
        failf(data, "Failed to send GSS-API authentication token.");
        gss_release_name(&gss_status, &server);
        gss_release_buffer(&gss_status, &gss_recv_token);
        gss_release_buffer(&gss_status, &gss_send_token);
        gss_delete_sec_context(&gss_status, &gss_context, NULL);
        return CURLE_COULDNT_CONNECT;
      }