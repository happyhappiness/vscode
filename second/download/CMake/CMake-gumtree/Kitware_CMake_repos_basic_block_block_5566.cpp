{
    memcpy(socksreq, &gss_enc, 1);
    code = Curl_write_plain(conn, sock, (char *)socksreq, 1, &written);
    if(code || (1 != written)) {
      failf(data, "Failed to send SSPI encryption type.");
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }
  }