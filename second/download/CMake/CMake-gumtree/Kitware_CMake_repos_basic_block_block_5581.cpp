{
    TCHAR *sname;

    sname = Curl_convert_UTF8_to_tchar(service_name);
    if(!sname)
      return CURLE_OUT_OF_MEMORY;

    status = s_pSecFn->InitializeSecurityContext(&cred_handle,
                                                 context_handle,
                                                 sname,
                                                 ISC_REQ_MUTUAL_AUTH |
                                                 ISC_REQ_ALLOCATE_MEMORY |
                                                 ISC_REQ_CONFIDENTIALITY |
                                                 ISC_REQ_REPLAY_DETECT,
                                                 0,
                                                 SECURITY_NATIVE_DREP,
                                                 &input_desc,
                                                 0,
                                                 &sspi_context,
                                                 &output_desc,
                                                 &sspi_ret_flags,
                                                 &expiry);

    Curl_unicodefree(sname);

    if(sspi_recv_token.pvBuffer) {
      s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
      sspi_recv_token.pvBuffer = NULL;
      sspi_recv_token.cbBuffer = 0;
    }

    if(check_sspi_err(conn, status, "InitializeSecurityContext")) {
      free(service_name);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      if(sspi_recv_token.pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
      failf(data, "Failed to initialise security context.");
      return CURLE_COULDNT_CONNECT;
    }

    if(sspi_send_token.cbBuffer != 0) {
      socksreq[0] = 1;    /* GSS-API subnegotiation version */
      socksreq[1] = 1;    /* authentication message type */
      us_length = htons((short)sspi_send_token.cbBuffer);
      memcpy(socksreq+2, &us_length, sizeof(short));

      code = Curl_write_plain(conn, sock, (char *)socksreq, 4, &written);
      if(code || (4 != written)) {
        failf(data, "Failed to send SSPI authentication request.");
        free(service_name);
        if(sspi_send_token.pvBuffer)
          s_pSecFn->FreeContextBuffer(sspi_send_token.pvBuffer);
        if(sspi_recv_token.pvBuffer)
          s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
        s_pSecFn->FreeCredentialsHandle(&cred_handle);
        s_pSecFn->DeleteSecurityContext(&sspi_context);
        return CURLE_COULDNT_CONNECT;
      }

      code = Curl_write_plain(conn, sock, (char *)sspi_send_token.pvBuffer,
                              sspi_send_token.cbBuffer, &written);
      if(code || (sspi_send_token.cbBuffer != (size_t)written)) {
        failf(data, "Failed to send SSPI authentication token.");
        free(service_name);
        if(sspi_send_token.pvBuffer)
          s_pSecFn->FreeContextBuffer(sspi_send_token.pvBuffer);
        if(sspi_recv_token.pvBuffer)
          s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
        s_pSecFn->FreeCredentialsHandle(&cred_handle);
        s_pSecFn->DeleteSecurityContext(&sspi_context);
        return CURLE_COULDNT_CONNECT;
      }

    }

    if(sspi_send_token.pvBuffer) {
      s_pSecFn->FreeContextBuffer(sspi_send_token.pvBuffer);
      sspi_send_token.pvBuffer = NULL;
    }
    sspi_send_token.cbBuffer = 0;

    if(sspi_recv_token.pvBuffer) {
      s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
      sspi_recv_token.pvBuffer = NULL;
    }
    sspi_recv_token.cbBuffer = 0;

    if(status != SEC_I_CONTINUE_NEEDED)
      break;

    /* analyse response */

    /*   GSS-API response looks like
     * +----+------+-----+----------------+
     * |VER | MTYP | LEN |     TOKEN      |
     * +----+------+----------------------+
     * | 1  |  1   |  2  | up to 2^16 - 1 |
     * +----+------+-----+----------------+
     */

    result = Curl_blockread_all(conn, sock, (char *)socksreq, 4, &actualread);
    if(result || (actualread != 4)) {
      failf(data, "Failed to receive SSPI authentication response.");
      free(service_name);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }

    /* ignore the first (VER) byte */
    if(socksreq[1] == 255) { /* status / message type */
      failf(data, "User was rejected by the SOCKS5 server (%u %u).",
            (unsigned int)socksreq[0], (unsigned int)socksreq[1]);
      free(service_name);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }

    if(socksreq[1] != 1) { /* status / messgae type */
      failf(data, "Invalid SSPI authentication response type (%u %u).",
            (unsigned int)socksreq[0], (unsigned int)socksreq[1]);
      free(service_name);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }

    memcpy(&us_length, socksreq+2, sizeof(short));
    us_length = ntohs(us_length);

    sspi_recv_token.cbBuffer = us_length;
    sspi_recv_token.pvBuffer = malloc(us_length);

    if(!sspi_recv_token.pvBuffer) {
      free(service_name);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_OUT_OF_MEMORY;
    }
    result = Curl_blockread_all(conn, sock, (char *)sspi_recv_token.pvBuffer,
                                sspi_recv_token.cbBuffer, &actualread);

    if(result || (actualread != us_length)) {
      failf(data, "Failed to receive SSPI authentication token.");
      free(service_name);
      if(sspi_recv_token.pvBuffer)
        s_pSecFn->FreeContextBuffer(sspi_recv_token.pvBuffer);
      s_pSecFn->FreeCredentialsHandle(&cred_handle);
      s_pSecFn->DeleteSecurityContext(&sspi_context);
      return CURLE_COULDNT_CONNECT;
    }

    context_handle = &sspi_context;
  }