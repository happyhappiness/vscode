OM_uint32
Curl_gss_delete_sec_context_a(OM_uint32 * minor_status,
                              gss_ctx_id_t * context_handle,
                              gss_buffer_t output_token)

{
  int rc;

  rc = gss_delete_sec_context(minor_status, context_handle, output_token);

  if(rc != GSS_S_COMPLETE || !output_token ||
      !output_token->length || !output_token->value)
    return rc;

  /* No way to allocate a buffer here, because it will be released by
     gss_release_buffer(). The solution is to overwrite the EBCDIC buffer
     with ASCII to return it. */

  if(Curl_gss_convert_in_place(minor_status, output_token))
    return GSS_S_FAILURE;

  return rc;
}