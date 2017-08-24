{
  gss_ctx_id_t *context = app_data;
  gss_buffer_desc dec, enc;
  OM_uint32 maj, min;
  int state;
  int len;

  /* NOTE that the cast is safe, neither of the krb5, gnu gss and heimdal
   * libraries modify the input buffer in gss_seal()
   */
  dec.value = (void *)from;
  dec.length = length;
  maj = gss_seal(&min, *context,
                 level == PROT_PRIVATE,
                 GSS_C_QOP_DEFAULT,
                 &dec, &state, &enc);

  if(maj != GSS_S_COMPLETE)
    return -1;

  /* malloc a new buffer, in case gss_release_buffer doesn't work as
     expected */
  *to = malloc(enc.length);
  if(!*to)
    return -1;
  memcpy(*to, enc.value, enc.length);
  len = curlx_uztosi(enc.length);
  gss_release_buffer(&min, &enc);
  return len;
}