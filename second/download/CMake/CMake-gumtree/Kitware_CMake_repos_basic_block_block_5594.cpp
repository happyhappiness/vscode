{
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