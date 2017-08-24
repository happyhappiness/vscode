{ /* status / messgae type */
    failf(data, "Invalid GSS-API encryption response type (%d %d).",
          socksreq[0], socksreq[1]);
    gss_delete_sec_context(&gss_status, &gss_context, NULL);
    return CURLE_COULDNT_CONNECT;
  }