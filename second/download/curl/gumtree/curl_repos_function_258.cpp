void Curl_cleanup_negotiate(struct SessionHandle *data)
{
  OM_uint32 minor_status;
  struct negotiatedata *neg_ctx = &data->state.negotiate;

  if (neg_ctx->context != GSS_C_NO_CONTEXT)
    gss_delete_sec_context(&minor_status, &neg_ctx->context, GSS_C_NO_BUFFER);

  if (neg_ctx->output_token.length != 0)
    gss_release_buffer(&minor_status, &neg_ctx->output_token);

  if (neg_ctx->server_name != GSS_C_NO_NAME)
    gss_release_name(&minor_status, &neg_ctx->server_name);

  memset(neg_ctx, 0, sizeof(*neg_ctx));
}