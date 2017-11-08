OM_uint32 Curl_gss_init_sec_context(
    struct Curl_easy *data,
    OM_uint32 *minor_status,
    gss_ctx_id_t *context,
    gss_name_t target_name,
    gss_OID mech_type,
    gss_channel_bindings_t input_chan_bindings,
    gss_buffer_t input_token,
    gss_buffer_t output_token,
    const bool mutual_auth,
    OM_uint32 *ret_flags)
{
  OM_uint32 req_flags = GSS_C_REPLAY_FLAG;

  if(mutual_auth)
    req_flags |= GSS_C_MUTUAL_FLAG;

  if(data->set.gssapi_delegation & CURLGSSAPI_DELEGATION_POLICY_FLAG) {
#ifdef GSS_C_DELEG_POLICY_FLAG
    req_flags |= GSS_C_DELEG_POLICY_FLAG;
#else
    infof(data, "warning: support for CURLGSSAPI_DELEGATION_POLICY_FLAG not "
        "compiled in\n");
#endif
  }

  if(data->set.gssapi_delegation & CURLGSSAPI_DELEGATION_FLAG)
    req_flags |= GSS_C_DELEG_FLAG;

  return gss_init_sec_context(minor_status,
                              GSS_C_NO_CREDENTIAL, /* cred_handle */
                              context,
                              target_name,
                              mech_type,
                              req_flags,
                              0, /* time_req */
                              input_chan_bindings,
                              input_token,
                              NULL, /* actual_mech_type */
                              output_token,
                              ret_flags,
                              NULL /* time_rec */);
}