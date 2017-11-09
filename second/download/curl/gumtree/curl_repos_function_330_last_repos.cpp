OM_uint32
Curl_gss_display_status_a(OM_uint32 * minor_status, OM_uint32 status_value,
                   int status_type, gss_OID mech_type,
                   gss_msg_ctx_t * message_context, gss_buffer_t status_string)

{
  int rc;

  rc = gss_display_status(minor_status, status_value, status_type,
                              mech_type, message_context, status_string);

  if(rc != GSS_S_COMPLETE || !status_string ||
     !status_string->length || !status_string->value)
    return rc;

  /* No way to allocate a buffer here, because it will be released by
     gss_release_buffer(). The solution is to overwrite the EBCDIC buffer
     with ASCII to return it. */

  if(Curl_gss_convert_in_place(minor_status, status_string))
    return GSS_S_FAILURE;

  return rc;
}