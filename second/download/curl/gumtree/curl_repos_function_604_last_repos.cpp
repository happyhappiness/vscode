OM_uint32 gss_import_name(OM_uint32 *min,
                          const gss_buffer_t input_name_buffer,
                          const gss_OID input_name_type,
                          gss_name_t *output_name)
{
  char *name = NULL;

  if(!min)
    return GSS_S_FAILURE;

  if(!input_name_buffer || !output_name) {
    *min = GSS_INVALID_ARGS;
    return GSS_S_FAILURE;
  }

  name = strndup(input_name_buffer->value, input_name_buffer->length);
  if(!name) {
    *min = GSS_NO_MEMORY;
    return GSS_S_FAILURE;
  }

  *output_name = (gss_name_t) name;
  *min = 0;

  return GSS_S_COMPLETE;
}