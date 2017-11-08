static int
krb5_decode(void *app_data, void *buf, int len, int level,
            struct connectdata *conn)
{
  gss_ctx_id_t *context = app_data;
  OM_uint32 maj, min;
  gss_buffer_desc enc, dec;

  /* shut gcc up */
  level = 0;
  conn = NULL;

  enc.value = buf;
  enc.length = len;
  maj = gss_unseal(&min, *context, &enc, &dec, NULL, NULL);
  if(maj != GSS_S_COMPLETE) {
    if(len >= 4)
      strcpy(buf, "599 ");
    return -1;
  }

  memcpy(buf, dec.value, dec.length);
  len = dec.length;
  gss_release_buffer(&min, &dec);

  return len;
}