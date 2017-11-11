OM_uint32 gss_init_sec_context(OM_uint32 *min,
            gss_const_cred_id_t initiator_cred_handle,
            gss_ctx_id_t *context_handle,
            gss_const_name_t target_name,
            const gss_OID mech_type,
            OM_uint32 req_flags,
            OM_uint32 time_req,
            const gss_channel_bindings_t input_chan_bindings,
            const gss_buffer_t input_token,
            gss_OID *actual_mech_type,
            gss_buffer_t output_token,
            OM_uint32 *ret_flags,
            OM_uint32 *time_rec)
{
  /* The token will be encoded in base64 */
  int length = APPROX_TOKEN_LEN * 3 / 4;
  int used = 0;
  char *token = NULL;
  const char *creds = NULL;
  gss_ctx_id_t ctx = NULL;

  if(!min)
    return GSS_S_FAILURE;

  *min = 0;

  if(!context_handle || !target_name || !output_token) {
    *min = GSS_INVALID_ARGS;
    return GSS_S_FAILURE;
  }

  creds = getenv("CURL_STUB_GSS_CREDS");
  if(!creds || strlen(creds) >= MAX_CREDS_LENGTH) {
    *min = GSS_INVALID_CREDS;
    return GSS_S_FAILURE;
  }

  ctx = *context_handle;
  if(ctx && strcmp(ctx->creds, creds)) {
    *min = GSS_INVALID_CREDS;
    return GSS_S_FAILURE;
  }

  output_token->length = 0;
  output_token->value = NULL;

  if(input_token && input_token->length) {
    if(!ctx) {
      *min = GSS_INVALID_CTX;
      return GSS_S_FAILURE;
    }

    /* Server response, either D (RA==) or C (Qw==) */
    if(((char *) input_token->value)[0] == 'D') {
      /* Done */
      switch(ctx->sent) {
      case KRB5:
      case NTLM3:
        if(ret_flags)
          *ret_flags = ctx->flags;
        if(time_rec)
          *time_rec = GSS_C_INDEFINITE;
        return GSS_S_COMPLETE;
      default:
        *min = GSS_SERVER_ERR;
        return GSS_S_FAILURE;
      }
    }

    if(((char *) input_token->value)[0] != 'C') {
      /* We only support Done or Continue */
      *min = GSS_SERVER_ERR;
      return GSS_S_FAILURE;
    }

    /* Continue */
    switch(ctx->sent) {
    case KRB5:
      /* We sent KRB5 and it failed, let's try NTLM */
      if(ctx->have_ntlm) {
        ctx->sent = NTLM1;
        break;
      }
      else {
        *min = GSS_SERVER_ERR;
        return GSS_S_FAILURE;
      }
    case NTLM1:
      ctx->sent = NTLM3;
      break;
    default:
      *min = GSS_SERVER_ERR;
      return GSS_S_FAILURE;
    }
  }
  else {
    if(ctx) {
      *min = GSS_INVALID_CTX;
      return GSS_S_FAILURE;
    }

    ctx = (gss_ctx_id_t) calloc(sizeof(*ctx), 1);
    if(!ctx) {
      *min = GSS_NO_MEMORY;
      return GSS_S_FAILURE;
    }

    if(strstr(creds, "KRB5"))
      ctx->have_krb5 = 1;

    if(strstr(creds, "NTLM"))
      ctx->have_ntlm = 1;

    if(ctx->have_krb5)
      ctx->sent = KRB5;
    else if(ctx->have_ntlm)
      ctx->sent = NTLM1;
    else {
      free(ctx);
      *min = GSS_NO_MECH;
      return GSS_S_FAILURE;
    }

    strcpy(ctx->creds, creds);
    ctx->flags = req_flags;
  }

  token = malloc(length);
  if(!token) {
    free(ctx);
    *min = GSS_NO_MEMORY;
    return GSS_S_FAILURE;
  }

  /* Token format: creds:target:type:padding */
  used = snprintf(token, length, "%s:%s:%d:", creds,
                  (char *) target_name, ctx->sent);

  if(used >= length) {
    free(token);
    free(ctx);
    *min = GSS_NO_MEMORY;
    return GSS_S_FAILURE;
  }

  /* Overwrite null terminator */
  memset(token + used, 'A', length - used);

  *context_handle = ctx;

  output_token->value = token;
  output_token->length = length;

  return GSS_S_CONTINUE_NEEDED;
}