OM_uint32 gss_delete_sec_context(OM_uint32 *min,
                                 gss_ctx_id_t *context_handle,
                                 gss_buffer_t output_token)
{
  if(!min)
    return GSS_S_FAILURE;

  if(!context_handle) {
    *min = GSS_INVALID_CTX;
    return GSS_S_FAILURE;
  }

  free(*context_handle);
  *context_handle = NULL;
  *min = 0;

  return GSS_S_COMPLETE;
}