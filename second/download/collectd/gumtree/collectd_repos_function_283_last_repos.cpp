static char *camqp_bytes_cstring(amqp_bytes_t *in) /* {{{ */
{
  char *ret;

  if ((in == NULL) || (in->bytes == NULL))
    return NULL;

  ret = malloc(in->len + 1);
  if (ret == NULL)
    return NULL;

  memcpy(ret, in->bytes, in->len);
  ret[in->len] = 0;

  return ret;
}