int Curl_schannel_shutdown(struct connectdata *conn, int sockindex)
{
  /* See https://msdn.microsoft.com/en-us/library/windows/desktop/aa380138.aspx
   * Shutting Down an Schannel Connection
   */
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
    conn->host.name;

  infof(data, "schannel: shutting down SSL/TLS connection with %s port %hu\n",
        hostname, conn->remote_port);

  if(connssl->cred && connssl->ctxt) {
    SecBufferDesc BuffDesc;
    SecBuffer Buffer;
    SECURITY_STATUS sspi_status;
    SecBuffer outbuf;
    SecBufferDesc outbuf_desc;
    CURLcode result;
    TCHAR *host_name;
    DWORD dwshut = SCHANNEL_SHUTDOWN;

    InitSecBuffer(&Buffer, SECBUFFER_TOKEN, &dwshut, sizeof(dwshut));
    InitSecBufferDesc(&BuffDesc, &Buffer, 1);

    sspi_status = s_pSecFn->ApplyControlToken(&connssl->ctxt->ctxt_handle,
                                              &BuffDesc);

    if(sspi_status != SEC_E_OK)
      failf(data, "schannel: ApplyControlToken failure: %s",
            Curl_sspi_strerror(conn, sspi_status));

    host_name = Curl_convert_UTF8_to_tchar(hostname);
    if(!host_name)
      return CURLE_OUT_OF_MEMORY;

    /* setup output buffer */
    InitSecBuffer(&outbuf, SECBUFFER_EMPTY, NULL, 0);
    InitSecBufferDesc(&outbuf_desc, &outbuf, 1);

    sspi_status = s_pSecFn->InitializeSecurityContext(
      &connssl->cred->cred_handle,
      &connssl->ctxt->ctxt_handle,
      host_name,
      connssl->req_flags,
      0,
      0,
      NULL,
      0,
      &connssl->ctxt->ctxt_handle,
      &outbuf_desc,
      &connssl->ret_flags,
      &connssl->ctxt->time_stamp);

    Curl_unicodefree(host_name);

    if((sspi_status == SEC_E_OK) || (sspi_status == SEC_I_CONTEXT_EXPIRED)) {
      /* send close message which is in output buffer */
      ssize_t written;
      result = Curl_write_plain(conn, conn->sock[sockindex], outbuf.pvBuffer,
                                outbuf.cbBuffer, &written);

      s_pSecFn->FreeContextBuffer(outbuf.pvBuffer);
      if((result != CURLE_OK) || (outbuf.cbBuffer != (size_t) written)) {
        infof(data, "schannel: failed to send close msg: %s"
              " (bytes written: %zd)\n", curl_easy_strerror(result), written);
      }
    }
  }

  /* free SSPI Schannel API security context handle */
  if(connssl->ctxt) {
    infof(data, "schannel: clear security context handle\n");
    s_pSecFn->DeleteSecurityContext(&connssl->ctxt->ctxt_handle);
    Curl_safefree(connssl->ctxt);
  }

  /* free SSPI Schannel API credential handle */
  if(connssl->cred) {
    Curl_ssl_sessionid_lock(conn);
    Curl_schannel_session_free(connssl->cred);
    Curl_ssl_sessionid_unlock(conn);
    connssl->cred = NULL;
  }

  /* free internal buffer for received encrypted data */
  if(connssl->encdata_buffer != NULL) {
    Curl_safefree(connssl->encdata_buffer);
    connssl->encdata_length = 0;
    connssl->encdata_offset = 0;
    connssl->encdata_is_incomplete = false;
  }

  /* free internal buffer for received decrypted data */
  if(connssl->decdata_buffer != NULL) {
    Curl_safefree(connssl->decdata_buffer);
    connssl->decdata_length = 0;
    connssl->decdata_offset = 0;
  }

  return CURLE_OK;
}