OM_uint32 gss_display_status(OM_uint32 *min,
                             OM_uint32 status_value,
                             int status_type,
                             const gss_OID mech_type,
                             OM_uint32 *message_context,
                             gss_buffer_t status_string)
{
  const char maj_str[] = "Stub GSS error";
  if(min)
    *min = 0;

  if(message_context)
    *message_context = 0;

  if(status_string) {
    status_string->value = NULL;
    status_string->length = 0;

    if(status_value >= GSS_LAST)
      return GSS_S_FAILURE;

    switch(status_type) {
      case GSS_C_GSS_CODE:
        status_string->value = strdup(maj_str);
        break;
      case GSS_C_MECH_CODE:
        status_string->value = strdup(min_err_table[status_value]);
        break;
      default:
        return GSS_S_FAILURE;
    }

    if(status_string->value)
      status_string->length = strlen(status_string->value);
    else
       return GSS_S_FAILURE;
  }

  return GSS_S_COMPLETE;
}