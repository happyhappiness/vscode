CURLcode Curl_sasl_create_ntlm_type3_message(struct SessionHandle *data,
                                             const char *userp,
                                             const char *passwdp,
                                             struct ntlmdata *ntlm,
                                             char **outptr, size_t *outlen)
{
  CURLcode result = CURLE_OK;
  SecBuffer type_2_buf;
  SecBuffer type_3_buf;
  SecBufferDesc type_2_desc;
  SecBufferDesc type_3_desc;
  SECURITY_STATUS status;
  unsigned long attrs;
  TimeStamp expiry; /* For Windows 9x compatibility of SSPI calls */

  (void) passwdp;
  (void) userp;

  /* Setup the type-2 "input" security buffer */
  type_2_desc.ulVersion = SECBUFFER_VERSION;
  type_2_desc.cBuffers  = 1;
  type_2_desc.pBuffers  = &type_2_buf;
  type_2_buf.BufferType = SECBUFFER_TOKEN;
  type_2_buf.pvBuffer   = ntlm->input_token;
  type_2_buf.cbBuffer   = curlx_uztoul(ntlm->input_token_len);

  /* Setup the type-3 "output" security buffer */
  type_3_desc.ulVersion = SECBUFFER_VERSION;
  type_3_desc.cBuffers  = 1;
  type_3_desc.pBuffers  = &type_3_buf;
  type_3_buf.BufferType = SECBUFFER_TOKEN;
  type_3_buf.pvBuffer   = ntlm->output_token;
  type_3_buf.cbBuffer   = curlx_uztoul(ntlm->token_max);

  /* Generate our type-3 message */
  status = s_pSecFn->InitializeSecurityContext(ntlm->credentials,
                                               ntlm->context,
                                               (TCHAR *) TEXT(""),
                                               0, 0, SECURITY_NETWORK_DREP,
                                               &type_2_desc,
                                               0, ntlm->context,
                                               &type_3_desc,
                                               &attrs, &expiry);
  if(status != SEC_E_OK) {
    infof(data, "NTLM handshake failure (type-3 message): Status=%x\n",
          status);

    return CURLE_RECV_ERROR;
  }

  /* Base64 encode the response */
  result = Curl_base64_encode(data, (char *) ntlm->output_token,
                              type_3_buf.cbBuffer, outptr, outlen);

  Curl_sasl_ntlm_cleanup(ntlm);

  return result;
}