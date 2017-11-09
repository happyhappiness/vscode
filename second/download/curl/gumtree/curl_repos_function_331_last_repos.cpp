OM_uint32
Curl_gss_init_sec_context_a(OM_uint32 * minor_status,
                            gss_cred_id_t cred_handle,
                            gss_ctx_id_t * context_handle,
                            gss_name_t target_name, gss_OID mech_type,
                            gss_flags_t req_flags, OM_uint32 time_req,
                            gss_channel_bindings_t input_chan_bindings,
                            gss_buffer_t input_token,
                            gss_OID * actual_mech_type,
                            gss_buffer_t output_token, gss_flags_t * ret_flags,
                            OM_uint32 * time_rec)

{
  int rc;
  unsigned int i;
  gss_buffer_desc in;
  gss_buffer_t inp;

  in.value = NULL;

  if((inp = input_token))
    if(inp->length && inp->value) {
      i = inp->length;

      if(!(in.value = malloc(i + 1))) {
        if(minor_status)
          *minor_status = ENOMEM;

        return GSS_S_FAILURE;
        }

      QadrtConvertA2E(in.value, input_token->value, i, i);
      ((char *) in.value)[i] = '\0';
      in.length = i;
      inp = &in;
      }

  rc = gss_init_sec_context(minor_status, cred_handle, context_handle,
                             target_name, mech_type, req_flags, time_req,
                             input_chan_bindings, inp, actual_mech_type,
                             output_token, ret_flags, time_rec);
  free(in.value);

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