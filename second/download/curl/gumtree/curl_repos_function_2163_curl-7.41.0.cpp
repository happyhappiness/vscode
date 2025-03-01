static ssize_t
schannel_recv(struct connectdata *conn, int sockindex,
              char *buf, size_t len, CURLcode *err)
{
  size_t size = 0;
  ssize_t nread = 0, ret = -1;
  CURLcode result;
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  unsigned char *reallocated_buffer;
  size_t reallocated_length;
  bool done = FALSE;
  SecBuffer inbuf[4];
  SecBufferDesc inbuf_desc;
  SECURITY_STATUS sspi_status = SEC_E_OK;

  infof(data, "schannel: client wants to read %zu bytes\n", len);
  *err = CURLE_OK;

  /* buffer to store previously received and decrypted data */
  if(connssl->decdata_buffer == NULL) {
    connssl->decdata_offset = 0;
    connssl->decdata_length = CURL_SCHANNEL_BUFFER_INIT_SIZE;
    connssl->decdata_buffer = malloc(connssl->decdata_length);
    if(connssl->decdata_buffer == NULL) {
      failf(data, "schannel: unable to allocate memory");
      *err = CURLE_OUT_OF_MEMORY;
      return -1;
    }
  }

  /* increase buffer in order to fit the requested amount of data */
  if(connssl->encdata_length - connssl->encdata_offset <
     CURL_SCHANNEL_BUFFER_FREE_SIZE || connssl->encdata_length < len) {
    /* increase internal encrypted data buffer */
    reallocated_length = connssl->encdata_offset +
                         CURL_SCHANNEL_BUFFER_FREE_SIZE;
    /* make sure that the requested amount of data fits */
    if(reallocated_length < len) {
      reallocated_length = len;
    }
    reallocated_buffer = realloc(connssl->encdata_buffer,
                                 reallocated_length);

    if(reallocated_buffer == NULL) {
      failf(data, "schannel: unable to re-allocate memory");
      *err = CURLE_OUT_OF_MEMORY;
      return -1;
    }
    else {
      connssl->encdata_buffer = reallocated_buffer;
      connssl->encdata_length = reallocated_length;
    }
  }

  /* read encrypted data from socket */
  infof(data, "schannel: encrypted data buffer: offset %zu length %zu\n",
        connssl->encdata_offset, connssl->encdata_length);
  size = connssl->encdata_length - connssl->encdata_offset;
  if(size > 0) {
    *err = Curl_read_plain(conn->sock[sockindex],
                  (char *) (connssl->encdata_buffer + connssl->encdata_offset),
                           size, &nread);
    /* check for received data */
    if(*err != CURLE_OK)
      ret = -1;
    else {
      if(nread > 0)
        /* increase encrypted data buffer offset */
        connssl->encdata_offset += nread;
      ret = nread;
    }
    infof(data, "schannel: encrypted data got %zd\n", ret);
  }

  infof(data, "schannel: encrypted data buffer: offset %zu length %zu\n",
        connssl->encdata_offset, connssl->encdata_length);

  /* check if we still have some data in our buffers */
  while(connssl->encdata_offset > 0 && sspi_status == SEC_E_OK &&
        connssl->decdata_offset < len) {
    /* prepare data buffer for DecryptMessage call */
    InitSecBuffer(&inbuf[0], SECBUFFER_DATA, connssl->encdata_buffer,
                  curlx_uztoul(connssl->encdata_offset));

    /* we need 3 more empty input buffers for possible output */
    InitSecBuffer(&inbuf[1], SECBUFFER_EMPTY, NULL, 0);
    InitSecBuffer(&inbuf[2], SECBUFFER_EMPTY, NULL, 0);
    InitSecBuffer(&inbuf[3], SECBUFFER_EMPTY, NULL, 0);

    InitSecBufferDesc(&inbuf_desc, inbuf, 4);

    /* http://msdn.microsoft.com/en-us/library/windows/desktop/aa375348.aspx */
    sspi_status = s_pSecFn->DecryptMessage(&connssl->ctxt->ctxt_handle,
                                           &inbuf_desc, 0, NULL);

    /* check if we need more data */
    if(sspi_status == SEC_E_INCOMPLETE_MESSAGE) {
      infof(data, "schannel: failed to decrypt data, need more data\n");
      *err = CURLE_AGAIN;
      return -1;
    }

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
        if(connssl->decdata_length - connssl->decdata_offset < size ||
           connssl->decdata_length < len) {
          /* increase internal decrypted data buffer */
          reallocated_length = connssl->decdata_offset + size;
          /* make sure that the requested amount of data fits */
          if(reallocated_length < len) {
            reallocated_length = len;
          }
          reallocated_buffer = realloc(connssl->decdata_buffer,
                                       reallocated_length);

          if(reallocated_buffer == NULL) {
            failf(data, "schannel: unable to re-allocate memory");
            *err = CURLE_OUT_OF_MEMORY;
            return -1;
          }
          else {
            connssl->decdata_buffer = reallocated_buffer;
            connssl->decdata_length = reallocated_length;
          }
        }

        /* copy decrypted data to internal buffer */
        size = inbuf[1].cbBuffer;
        if(size > 0) {
          memcpy(connssl->decdata_buffer + connssl->decdata_offset,
                 inbuf[1].pvBuffer, size);
          connssl->decdata_offset += size;
        }

        infof(data, "schannel: decrypted data added: %zu\n", size);
        infof(data, "schannel: decrypted data cached: offset %zu length %zu\n",
              connssl->decdata_offset, connssl->decdata_length);
      }

      /* check for remaining encrypted data */
      if(inbuf[3].BufferType == SECBUFFER_EXTRA && inbuf[3].cbBuffer > 0) {
        infof(data, "schannel: encrypted data length: %lu\n",
              inbuf[3].cbBuffer);

        /* check if the remaining data is less than the total amount
         * and therefore begins after the already processed data
        */
        if(connssl->encdata_offset > inbuf[3].cbBuffer) {
          /* move remaining encrypted data forward to the beginning of
             buffer */
          memmove(connssl->encdata_buffer,
                  (connssl->encdata_buffer + connssl->encdata_offset) -
                    inbuf[3].cbBuffer, inbuf[3].cbBuffer);
          connssl->encdata_offset = inbuf[3].cbBuffer;
        }

        infof(data, "schannel: encrypted data cached: offset %zu length %zu\n",
              connssl->encdata_offset, connssl->encdata_length);
      }
      else{
        /* reset encrypted buffer offset, because there is no data remaining */
        connssl->encdata_offset = 0;
      }
    }

    /* check if server wants to renegotiate the connection context */
    if(sspi_status == SEC_I_RENEGOTIATE) {
      infof(data, "schannel: remote party requests SSL/TLS renegotiation\n");

      /* begin renegotiation */
      infof(data, "schannel: renegotiating SSL/TLS connection\n");
      connssl->state = ssl_connection_negotiating;
      connssl->connecting_state = ssl_connect_2_writing;
      result = schannel_connect_common(conn, sockindex, FALSE, &done);
      if(result)
        *err = result;
      else {
        infof(data, "schannel: SSL/TLS connection renegotiated\n");
        /* now retry receiving data */
        return schannel_recv(conn, sockindex, buf, len, err);
      }
    }
  }

  infof(data, "schannel: decrypted data buffer: offset %zu length %zu\n",
        connssl->decdata_offset, connssl->decdata_length);

  /* copy requested decrypted data to supplied buffer */
  size = len < connssl->decdata_offset ? len : connssl->decdata_offset;
  if(size > 0) {
    memcpy(buf, connssl->decdata_buffer, size);
    ret = size;

    /* move remaining decrypted data forward to the beginning of buffer */
    memmove(connssl->decdata_buffer, connssl->decdata_buffer + size,
            connssl->decdata_offset - size);
    connssl->decdata_offset -= size;

    infof(data, "schannel: decrypted data returned %zd\n", size);
    infof(data, "schannel: decrypted data buffer: offset %zu length %zu\n",
          connssl->decdata_offset, connssl->decdata_length);
  }
  else
    ret = 0;

  /* check if the server closed the connection */
  if(ret <= 0 && ( /* special check for Windows 2000 Professional */
      sspi_status == SEC_I_CONTEXT_EXPIRED || (sspi_status == SEC_E_OK &&
        connssl->encdata_offset > 0 && connssl->encdata_buffer[0] == 0x15))) {
    infof(data, "schannel: server closed the connection\n");
    *err = CURLE_OK;
    return 0;
  }

  /* check if something went wrong and we need to return an error */
  if(ret < 0 && sspi_status != SEC_E_OK) {
    infof(data, "schannel: failed to read data from server: %s\n",
          Curl_sspi_strerror(conn, sspi_status));
    *err = CURLE_RECV_ERROR;
    return -1;
  }

  return ret;
}