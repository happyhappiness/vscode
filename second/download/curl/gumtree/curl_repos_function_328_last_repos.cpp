static int
Curl_gss_convert_in_place(OM_uint32 * minor_status, gss_buffer_t buf)

{
  unsigned int i;
  char * t;

  /* Convert `buf' in place, from EBCDIC to ASCII.
     If error, release the buffer and return -1. Else return 0. */

  i = buf->length;

  if(i) {
    if(!(t = malloc(i))) {
      gss_release_buffer(minor_status, buf);

      if(minor_status)
        *minor_status = ENOMEM;

      return -1;
      }

    QadrtConvertE2A(t, buf->value, i, i);
    memcpy(buf->value, t, i);
    free(t);
    }

  return 0;
}