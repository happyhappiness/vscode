OM_uint32 gss_release_buffer(OM_uint32 *min,
                             gss_buffer_t buffer)
{
  if(min)
    *min = 0;

  if(buffer && buffer->length) {
    free(buffer->value);
    buffer->length = 0;
  }

  return GSS_S_COMPLETE;
}