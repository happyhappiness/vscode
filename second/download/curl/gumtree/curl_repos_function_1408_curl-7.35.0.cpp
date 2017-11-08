int Curl_input_negotiate(struct connectdata *conn, bool proxy,
                         const char *header)
{
  struct negotiatedata *neg_ctx = proxy?&conn->data->state.proxyneg:
    &conn->data->state.negotiate;
  BYTE              *input_token = 0;
  SecBufferDesc     out_buff_desc;
  SecBuffer         out_sec_buff;
  SecBufferDesc     in_buff_desc;
  SecBuffer         in_sec_buff;
  unsigned long     context_attributes;
  TimeStamp         lifetime;
  TCHAR             *sname;
  int ret;
  size_t len = 0, input_token_len = 0;
  bool gss = FALSE;
  const char* protocol;
  CURLcode error;

  if(checkprefix("GSS-Negotiate", header)) {
    protocol = "GSS-Negotiate";
    gss = TRUE;
  }
  else if(checkprefix("Negotiate", header)) {
    protocol = "Negotiate";
    gss = FALSE;
  }
  else
    return -1;

  if(neg_ctx->context) {
    if(neg_ctx->gss != gss) {
      return -1;
    }
  }
  else {
    neg_ctx->protocol = protocol;
    neg_ctx->gss = gss;
  }

  if(neg_ctx->context && neg_ctx->status == SEC_E_OK) {
    /* We finished successfully our part of authentication, but server
     * rejected it (since we're again here). Exit with an error since we
     * can't invent anything better */
    Curl_cleanup_negotiate(conn->data);
    return -1;
  }

  if(0 == strlen(neg_ctx->server_name)) {
    ret = get_gss_name(conn, proxy, neg_ctx);
    if(ret)
      return ret;
  }

  if(!neg_ctx->output_token) {
    PSecPkgInfo SecurityPackage;
    ret = s_pSecFn->QuerySecurityPackageInfo((TCHAR *) TEXT("Negotiate"),
                                             &SecurityPackage);
    if(ret != SEC_E_OK)
      return -1;

    /* Allocate input and output buffers according to the max token size
       as indicated by the security package */
    neg_ctx->max_token_length = SecurityPackage->cbMaxToken;
    neg_ctx->output_token = malloc(neg_ctx->max_token_length);
    s_pSecFn->FreeContextBuffer(SecurityPackage);
  }

  /* Obtain the input token, if any */
  header += strlen(neg_ctx->protocol);
  while(*header && ISSPACE(*header))
    header++;

  len = strlen(header);
  if(!len) {
    /* first call in a new negotation, we have to acquire credentials,
       and allocate memory for the context */

    neg_ctx->credentials = malloc(sizeof(CredHandle));
    neg_ctx->context = malloc(sizeof(CtxtHandle));

    if(!neg_ctx->credentials || !neg_ctx->context)
      return -1;

    neg_ctx->status =
      s_pSecFn->AcquireCredentialsHandle(NULL,
                                         (TCHAR *) TEXT("Negotiate"),
                                         SECPKG_CRED_OUTBOUND, NULL, NULL,
                                         NULL, NULL, neg_ctx->credentials,
                                         &lifetime);
    if(neg_ctx->status != SEC_E_OK)
      return -1;
  }
  else {
    input_token = malloc(neg_ctx->max_token_length);
    if(!input_token)
      return -1;

    error = Curl_base64_decode(header,
                               (unsigned char **)&input_token,
                               &input_token_len);
    if(error || input_token_len == 0)
      return -1;
  }

  /* prepare the output buffers, and input buffers if present */
  out_buff_desc.ulVersion = 0;
  out_buff_desc.cBuffers  = 1;
  out_buff_desc.pBuffers  = &out_sec_buff;

  out_sec_buff.cbBuffer   = curlx_uztoul(neg_ctx->max_token_length);
  out_sec_buff.BufferType = SECBUFFER_TOKEN;
  out_sec_buff.pvBuffer   = neg_ctx->output_token;


  if(input_token) {
    in_buff_desc.ulVersion = 0;
    in_buff_desc.cBuffers  = 1;
    in_buff_desc.pBuffers  = &in_sec_buff;

    in_sec_buff.cbBuffer   = curlx_uztoul(input_token_len);
    in_sec_buff.BufferType = SECBUFFER_TOKEN;
    in_sec_buff.pvBuffer   = input_token;
  }

  sname = Curl_convert_UTF8_to_tchar(neg_ctx->server_name);
  if(!sname)
    return CURLE_OUT_OF_MEMORY;

  neg_ctx->status = s_pSecFn->InitializeSecurityContext(
    neg_ctx->credentials,
    input_token ? neg_ctx->context : 0,
    sname,
    ISC_REQ_CONFIDENTIALITY,
    0,
    SECURITY_NATIVE_DREP,
    input_token ? &in_buff_desc : 0,
    0,
    neg_ctx->context,
    &out_buff_desc,
    &context_attributes,
    &lifetime);

  Curl_unicodefree(sname);

  if(GSS_ERROR(neg_ctx->status))
    return -1;

  if(neg_ctx->status == SEC_I_COMPLETE_NEEDED ||
     neg_ctx->status == SEC_I_COMPLETE_AND_CONTINUE) {
    neg_ctx->status = s_pSecFn->CompleteAuthToken(neg_ctx->context,
                                                  &out_buff_desc);
    if(GSS_ERROR(neg_ctx->status))
      return -1;
  }

  neg_ctx->output_token_length = out_sec_buff.cbBuffer;

  return 0;
}