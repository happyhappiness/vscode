static ssize_t
schannel_recv(struct connectdata *conn, int sockindex,
              char *buf, size_t len, CURLcode *err)
{
  size_t size = 0;
  ssize_t nread = -1;
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  unsigned char *reallocated_buffer;
  size_t reallocated_length;
  bool done = FALSE;
  SecBuffer inbuf[4];
  SecBufferDesc inbuf_desc;
  SECURITY_STATUS sspi_status = SEC_E_OK;
  /* we want the length of the encrypted buffer to be at least large enough
     that it can hold all the bytes requested and some TLS record overhead. */
  size_t min_encdata_length = len + CURL_SCHANNEL_BUFFER_FREE_SIZE;

  /****************************************************************************
   * Don't return or set BACKEND->recv_unrecoverable_err unless in the cleanup.
   * The pattern for return error is set *err, optional infof, goto cleanup.
   *
   * Our priority is to always return as much decrypted data to the caller as
   * possible, even if an error occurs. The state of the decrypted buffer must
   * always be valid. Transfer of decrypted data to the caller's buffer is
   * handled in the cleanup.
   */

  infof(data, "schannel: client wants to read %zu bytes\n", len);
  *err = CURLE_OK;

  if(len && len <= BACKEND->decdata_offset) {
    infof(data, "schannel: enough decrypted data is already available\n");
    goto cleanup;
  }
  else if(BACKEND->recv_unrecoverable_err) {
    *err = BACKEND->recv_unrecoverable_err;
    infof(data, "schannel: an unrecoverable error occurred in a prior call\n");
    goto cleanup;
  }
  else if(BACKEND->recv_sspi_close_notify) {
    /* once a server has indicated shutdown there is no more encrypted data */
    infof(data, "schannel: server indicated shutdown in a prior call\n");
    goto cleanup;
  }
  else if(!len) {
    /* It's debatable what to return when !len. Regardless we can't return
    immediately because there may be data to decrypt (in the case we want to
    decrypt all encrypted cached data) so handle !len later in cleanup.
    */
    ; /* do nothing */
  }
  else if(!BACKEND->recv_connection_closed) {
    /* increase enc buffer in order to fit the requested amount of data */
    size = BACKEND->encdata_length - BACKEND->encdata_offset;
    if(size < CURL_SCHANNEL_BUFFER_FREE_SIZE ||
       BACKEND->encdata_length < min_encdata_length) {
      reallocated_length = BACKEND->encdata_offset +
                           CURL_SCHANNEL_BUFFER_FREE_SIZE;
      if(reallocated_length < min_encdata_length) {
        reallocated_length = min_encdata_length;
      }
      reallocated_buffer = realloc(BACKEND->encdata_buffer,
                                   reallocated_length);
      if(reallocated_buffer == NULL) {
        *err = CURLE_OUT_OF_MEMORY;
        failf(data, "schannel: unable to re-allocate memory");
        goto cleanup;
      }

      BACKEND->encdata_buffer = reallocated_buffer;
      BACKEND->encdata_length = reallocated_length;
      size = BACKEND->encdata_length - BACKEND->encdata_offset;
      infof(data, "schannel: encdata_buffer resized %zu\n",
            BACKEND->encdata_length);
    }

    infof(data, "schannel: encrypted data buffer: offset %zu length %zu\n",
          BACKEND->encdata_offset, BACKEND->encdata_length);

    /* read encrypted data from socket */
    *err = Curl_read_plain(conn->sock[sockindex],
                           (char *)(BACKEND->encdata_buffer +
                                    BACKEND->encdata_offset),
                           size, &nread);
    if(*err) {
      nread = -1;
      if(*err == CURLE_AGAIN)
        infof(data, "schannel: Curl_read_plain returned CURLE_AGAIN\n");
      else if(*err == CURLE_RECV_ERROR)
        infof(data, "schannel: Curl_read_plain returned CURLE_RECV_ERROR\n");
      else
        infof(data, "schannel: Curl_read_plain returned error %d\n", *err);
    }
    else if(nread == 0) {
      BACKEND->recv_connection_closed = true;
      infof(data, "schannel: server closed the connection\n");
    }
    else if(nread > 0) {
      BACKEND->encdata_offset += (size_t)nread;
      BACKEND->encdata_is_incomplete = false;
      infof(data, "schannel: encrypted data got %zd\n", nread);
    }
  }

  infof(data, "schannel: encrypted data buffer: offset %zu length %zu\n",
        BACKEND->encdata_offset, BACKEND->encdata_length);

  /* decrypt loop */
  while(BACKEND->encdata_offset > 0 && sspi_status == SEC_E_OK &&
        (!len || BACKEND->decdata_offset < len ||
         BACKEND->recv_connection_closed)) {
    /* prepare data buffer for DecryptMessage call */
    InitSecBuffer(&inbuf[0], SECBUFFER_DATA, BACKEND->encdata_buffer,
                  curlx_uztoul(BACKEND->encdata_offset));

    /* we need 3 more empty input buffers for possible output */
    InitSecBuffer(&inbuf[1], SECBUFFER_EMPTY, NULL, 0);
    InitSecBuffer(&inbuf[2], SECBUFFER_EMPTY, NULL, 0);
    InitSecBuffer(&inbuf[3], SECBUFFER_EMPTY, NULL, 0);
    InitSecBufferDesc(&inbuf_desc, inbuf, 4);

    /* https://msdn.microsoft.com/en-us/library/windows/desktop/aa375348.aspx
       */
    sspi_status = s_pSecFn->DecryptMessage(&BACKEND->ctxt->ctxt_handle,
                                           &inbuf_desc, 0, NULL);

    /* check if everything went fine (server may want to renegotiate
       or shutdown the connection context) */
    if(sspi_status == SEC_E_OK || sspi_status == SEC_I_RENEGOTIATE ||
       sspi_status == SEC_I_CONTEXT_EXPIRED) {
      /* check for successfully decrypted data, even before actual
         renegotiation or shutdown of the connection context */
      if(inbuf[1].BufferType == SECBUFFER_DATA) {
        infof(data, "schannel: decrypted data length: %lu\n",
              inbuf[1].cbBuffer);

        /* increase buffer in order to fit the received amount of data */
        size = inbuf[1].cbBuffer > CURL_SCHANNEL_BUFFER_FREE_SIZE ?
               inbuf[1].cbBuffer : CURL_SCHANNEL_BUFFER_FREE_SIZE;
        if(BACKEND->decdata_length - BACKEND->decdata_offset < size ||
           BACKEND->decdata_length < len) {
          /* increase internal decrypted data buffer */
          reallocated_length = BACKEND->decdata_offset + size;
          /* make sure that the requested amount of data fits */
          if(reallocated_length < len) {
            reallocated_length = len;
          }
          reallocated_buffer = realloc(BACKEND->decdata_buffer,
                                       reallocated_length);
          if(reallocated_buffer == NULL) {
            *err = CURLE_OUT_OF_MEMORY;
            failf(data, "schannel: unable to re-allocate memory");
            goto cleanup;
          }
          BACKEND->decdata_buffer = reallocated_buffer;
          BACKEND->decdata_length = reallocated_length;
        }

        /* copy decrypted data to internal buffer */
        size = inbuf[1].cbBuffer;
        if(size) {
          memcpy(BACKEND->decdata_buffer + BACKEND->decdata_offset,
                 inbuf[1].pvBuffer, size);
          BACKEND->decdata_offset += size;
        }

        infof(data, "schannel: decrypted data added: %zu\n", size);
        infof(data, "schannel: decrypted data cached: offset %zu length %zu\n",
              BACKEND->decdata_offset, BACKEND->decdata_length);
      }

      /* check for remaining encrypted data */
      if(inbuf[3].BufferType == SECBUFFER_EXTRA && inbuf[3].cbBuffer > 0) {
        infof(data, "schannel: encrypted data length: %lu\n",
              inbuf[3].cbBuffer);

        /* check if the remaining data is less than the total amount
         * and therefore begins after the already processed data
         */
        if(BACKEND->encdata_offset > inbuf[3].cbBuffer) {
          /* move remaining encrypted data forward to the beginning of
             buffer */
          memmove(BACKEND->encdata_buffer,
                  (BACKEND->encdata_buffer + BACKEND->encdata_offset) -
                  inbuf[3].cbBuffer, inbuf[3].cbBuffer);
          BACKEND->encdata_offset = inbuf[3].cbBuffer;
        }

        infof(data, "schannel: encrypted data cached: offset %zu length %zu\n",
              BACKEND->encdata_offset, BACKEND->encdata_length);
      }
      else {
        /* reset encrypted buffer offset, because there is no data remaining */
        BACKEND->encdata_offset = 0;
      }

      /* check if server wants to renegotiate the connection context */
      if(sspi_status == SEC_I_RENEGOTIATE) {
        infof(data, "schannel: remote party requests renegotiation\n");
        if(*err && *err != CURLE_AGAIN) {
          infof(data, "schannel: can't renogotiate, an error is pending\n");
          goto cleanup;
        }
        if(BACKEND->encdata_offset) {
          *err = CURLE_RECV_ERROR;
          infof(data, "schannel: can't renogotiate, "
                      "encrypted data available\n");
          goto cleanup;
        }
        /* begin renegotiation */
        infof(data, "schannel: renegotiating SSL/TLS connection\n");
        connssl->state = ssl_connection_negotiating;
        connssl->connecting_state = ssl_connect_2_writing;
        *err = schannel_connect_common(conn, sockindex, FALSE, &done);
        if(*err) {
          infof(data, "schannel: renegotiation failed\n");
          goto cleanup;
        }
        /* now retry receiving data */
        sspi_status = SEC_E_OK;
        infof(data, "schannel: SSL/TLS connection renegotiated\n");
        continue;
      }
      /* check if the server closed the connection */
      else if(sspi_status == SEC_I_CONTEXT_EXPIRED) {
        /* In Windows 2000 SEC_I_CONTEXT_EXPIRED (close_notify) is not
           returned so we have to work around that in cleanup. */
        BACKEND->recv_sspi_close_notify = true;
        if(!BACKEND->recv_connection_closed) {
          BACKEND->recv_connection_closed = true;
          infof(data, "schannel: server closed the connection\n");
        }
        goto cleanup;
      }
    }
    else if(sspi_status == SEC_E_INCOMPLETE_MESSAGE) {
      BACKEND->encdata_is_incomplete = true;
      if(!*err)
        *err = CURLE_AGAIN;
      infof(data, "schannel: failed to decrypt data, need more data\n");
      goto cleanup;
    }
    else {
      *err = CURLE_RECV_ERROR;
      infof(data, "schannel: failed to read data from server: %s\n",
            Curl_sspi_strerror(conn, sspi_status));
      goto cleanup;
    }
  }

  infof(data, "schannel: encrypted data buffer: offset %zu length %zu\n",
        BACKEND->encdata_offset, BACKEND->encdata_length);

  infof(data, "schannel: decrypted data buffer: offset %zu length %zu\n",
        BACKEND->decdata_offset, BACKEND->decdata_length);

cleanup:
  /* Warning- there is no guarantee the encdata state is valid at this point */
  infof(data, "schannel: schannel_recv cleanup\n");

  /* Error if the connection has closed without a close_notify.
  Behavior here is a matter of debate. We don't want to be vulnerable to a
  truncation attack however there's some browser precedent for ignoring the
  close_notify for compatibility reasons.
  Additionally, Windows 2000 (v5.0) is a special case since it seems it doesn't
  return close_notify. In that case if the connection was closed we assume it
  was graceful (close_notify) since there doesn't seem to be a way to tell.
  */
  if(len && !BACKEND->decdata_offset && BACKEND->recv_connection_closed &&
     !BACKEND->recv_sspi_close_notify) {
    bool isWin2k = Curl_verify_windows_version(5, 0, PLATFORM_WINNT,
                                               VERSION_EQUAL);

    if(isWin2k && sspi_status == SEC_E_OK)
      BACKEND->recv_sspi_close_notify = true;
    else {
      *err = CURLE_RECV_ERROR;
      infof(data, "schannel: server closed abruptly (missing close_notify)\n");
    }
  }

  /* Any error other than CURLE_AGAIN is an unrecoverable error. */
  if(*err && *err != CURLE_AGAIN)
      BACKEND->recv_unrecoverable_err = *err;

  size = len < BACKEND->decdata_offset ? len : BACKEND->decdata_offset;
  if(size) {
    memcpy(buf, BACKEND->decdata_buffer, size);
    memmove(BACKEND->decdata_buffer, BACKEND->decdata_buffer + size,
            BACKEND->decdata_offset - size);
    BACKEND->decdata_offset -= size;

    infof(data, "schannel: decrypted data returned %zu\n", size);
    infof(data, "schannel: decrypted data buffer: offset %zu length %zu\n",
          BACKEND->decdata_offset, BACKEND->decdata_length);
    *err = CURLE_OK;
    return (ssize_t)size;
  }

  if(!*err && !BACKEND->recv_connection_closed)
      *err = CURLE_AGAIN;

  /* It's debatable what to return when !len. We could return whatever error we
  got from decryption but instead we override here so the return is consistent.
  */
  if(!len)
    *err = CURLE_OK;

  return *err ? -1 : 0;
}