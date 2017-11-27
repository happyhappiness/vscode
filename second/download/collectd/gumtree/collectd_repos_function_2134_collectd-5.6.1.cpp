static int cj_cb_string (void *ctx, const unsigned char *val,
    yajl_len_t len)
{
  /* Handle the string as if it was a number. */
  return (cj_cb_number (ctx, (const char *) val, len));
}