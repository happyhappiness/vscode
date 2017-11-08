OM_uint32
Curl_gss_import_name_a(OM_uint32 * minor_status, gss_buffer_t in_name,
                       gss_OID in_name_type, gss_name_t * out_name)

{
  int rc;
  unsigned int i;
  gss_buffer_desc in;

  if(!in_name || !in_name->value || !in_name->length)
    return gss_import_name(minor_status, in_name, in_name_type, out_name);

  memcpy((char *) &in, (char *) in_name, sizeof in);
  i = in.length;

  if(!(in.value = malloc(i + 1))) {
    if(minor_status)
      *minor_status = ENOMEM;

    return GSS_S_FAILURE;
    }

  QadrtConvertA2E(in.value, in_name->value, i, i);
  ((char *) in.value)[i] = '\0';
  rc = gss_import_name(minor_status, &in, in_name_type, out_name);
  free(in.value);
  return rc;
}