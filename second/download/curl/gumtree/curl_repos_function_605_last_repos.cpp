OM_uint32 gss_release_name(OM_uint32 *min,
                           gss_name_t *input_name)
{
  if(min)
    *min = 0;

  if(input_name)
    free(*input_name);

  return GSS_S_COMPLETE;
}