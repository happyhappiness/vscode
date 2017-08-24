{
    if(doread) {
      /* read encrypted handshake data from socket */
      result = Curl_read_plain(conn->sock[sockindex],
                               (char *) (connssl->encdata_buffer +
                                         connssl->encdata_offset),
                               connssl->encdata_length -
                               connssl->encdata_offset,
                               &nread);
      if(result == CURLE_AGAIN) {
        if(connssl->connecting_state != ssl_connect_2_writing)
          connssl->connecting_state = ssl_connect_2_reading;
        infof(data, "schannel: failed to receive handshake, "
              "need more data\n");
        return CURLE_OK;
      }
      else if((result != CURLE_OK) || (nread == 0)) {
        failf(data, "schannel: failed to receive handshake, "
              "SSL/TLS connection failed");
        return CURLE_SSL_CONNECT_ERROR;
      }

      /* increase encrypted data buffer offset */
      connssl->encdata_offset += nread;
      connssl->encdata_is_incomplete = false;
      infof(data, "schannel: encrypted data got %zd\n", nread);
    }

    infof(data, "schannel: encrypted data buffer: offset %zu length %zu\n",
          connssl->encdata_offset, connssl->encdata_length);

    /* setup input buffers */
    InitSecBuffer(&inbuf[0], SECBUFFER_TOKEN, malloc(connssl->encdata_offset),
                  curlx_uztoul(connssl->encdata_offset));
    InitSecBuffer(&inbuf[1], SECBUFFER_EMPTY, NULL, 0);
    InitSecBufferDesc(&inbuf_desc, inbuf, 2);

    /* setup output buffers */
    InitSecBuffer(&outbuf[0], SECBUFFER_TOKEN, NULL, 0);
    InitSecBuffer(&outbuf[1], SECBUFFER_ALERT, NULL, 0);
    InitSecBuffer(&outbuf[2], SECBUFFER_EMPTY, NULL, 0);
    InitSecBufferDesc(&outbuf_desc, outbuf, 3);

    if(inbuf[0].pvBuffer == NULL) {
      failf(data, "schannel: unable to allocate memory");
      return CURLE_OUT_OF_MEMORY;
    }

    /* copy received handshake data into input buffer */
    memcpy(inbuf[0].pvBuffer, connssl->encdata_buffer,
           connssl->encdata_offset);

    host_name = Curl_convert_UTF8_to_tchar(hostname);
    if(!host_name)
      return CURLE_OUT_OF_MEMORY;

    /* https://msdn.microsoft.com/en-us/library/windows/desktop/aa375924.aspx
       */
    sspi_status = s_pSecFn->InitializeSecurityContext(
      &connssl->cred->cred_handle, &connssl->ctxt->ctxt_handle,
      host_name, connssl->req_flags, 0, 0, &inbuf_desc, 0, NULL,
      &outbuf_desc, &connssl->ret_flags, &connssl->ctxt->time_stamp);

    Curl_unicodefree(host_name);

    /* free buffer for received handshake data */
    Curl_safefree(inbuf[0].pvBuffer);

    /* check if the handshake was incomplete */
    if(sspi_status == SEC_E_INCOMPLETE_MESSAGE) {
      connssl->encdata_is_incomplete = true;
      connssl->connecting_state = ssl_connect_2_reading;
      infof(data, "schannel: received incomplete message, need more data\n");
      return CURLE_OK;
    }

    /* If the server has requested a client certificate, attempt to continue
       the handshake without one. This will allow connections to servers which
       request a client certificate but do not require it. */
    if(sspi_status == SEC_I_INCOMPLETE_CREDENTIALS &&
       !(connssl->req_flags & ISC_REQ_USE_SUPPLIED_CREDS)) {
      connssl->req_flags |= ISC_REQ_USE_SUPPLIED_CREDS;
      connssl->connecting_state = ssl_connect_2_writing;
      infof(data, "schannel: a client certificate has been requested\n");
      return CURLE_OK;
    }

    /* check if the handshake needs to be continued */
    if(sspi_status == SEC_I_CONTINUE_NEEDED || sspi_status == SEC_E_OK) {
      for(i = 0; i < 3; i++) {
        /* search for handshake tokens that need to be send */
        if(outbuf[i].BufferType == SECBUFFER_TOKEN && outbuf[i].cbBuffer > 0) {
          infof(data, "schannel: sending next handshake data: "
                "sending %lu bytes...\n", outbuf[i].cbBuffer);

          /* send handshake token to server */
          result = Curl_write_plain(conn, conn->sock[sockindex],
                                    outbuf[i].pvBuffer, outbuf[i].cbBuffer,
                                    &written);
          if((result != CURLE_OK) ||
             (outbuf[i].cbBuffer != (size_t) written)) {
            failf(data, "schannel: failed to send next handshake data: "
                  "sent %zd of %lu bytes", written, outbuf[i].cbBuffer);
            return CURLE_SSL_CONNECT_ERROR;
          }
        }

        /* free obsolete buffer */
        if(outbuf[i].pvBuffer != NULL) {
          s_pSecFn->FreeContextBuffer(outbuf[i].pvBuffer);
        }
      }
    }
    else {
      if(sspi_status == SEC_E_WRONG_PRINCIPAL)
        failf(data, "schannel: SNI or certificate check failed: %s",
              Curl_sspi_strerror(conn, sspi_status));
      else
        failf(data, "schannel: next InitializeSecurityContext failed: %s",
              Curl_sspi_strerror(conn, sspi_status));
      return sspi_status == SEC_E_UNTRUSTED_ROOT ?
          CURLE_SSL_CACERT_BADFILE : CURLE_SSL_CONNECT_ERROR;
    }

    /* check if there was additional remaining encrypted data */
    if(inbuf[1].BufferType == SECBUFFER_EXTRA && inbuf[1].cbBuffer > 0) {
      infof(data, "schannel: encrypted data length: %lu\n", inbuf[1].cbBuffer);
      /*
        There are two cases where we could be getting extra data here:
        1) If we're renegotiating a connection and the handshake is already
        complete (from the server perspective), it can encrypted app data
        (not handshake data) in an extra buffer at this point.
        2) (sspi_status == SEC_I_CONTINUE_NEEDED) We are negotiating a
        connection and this extra data is part of the handshake.
        We should process the data immediately; waiting for the socket to
        be ready may fail since the server is done sending handshake data.
      */
      /* check if the remaining data is less than the total amount
         and therefore begins after the already processed data */
      if(connssl->encdata_offset > inbuf[1].cbBuffer) {
        memmove(connssl->encdata_buffer,
                (connssl->encdata_buffer + connssl->encdata_offset) -
                inbuf[1].cbBuffer, inbuf[1].cbBuffer);
        connssl->encdata_offset = inbuf[1].cbBuffer;
        if(sspi_status == SEC_I_CONTINUE_NEEDED) {
          doread = FALSE;
          continue;
        }
      }
    }
    else {
      connssl->encdata_offset = 0;
    }
    break;
  }