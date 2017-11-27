static int csnmp_strvbcopy_hexstring (char *dst, /* {{{ */
    const struct variable_list *vb, size_t dst_size)
{
  char *buffer_ptr;
  size_t buffer_free;
  size_t i;

  buffer_ptr = dst;
  buffer_free = dst_size;

  for (i = 0; i < vb->val_len; i++)
  {
    int status;

    status = snprintf (buffer_ptr, buffer_free,
        (i == 0) ? "%02x" : ":%02x", (unsigned int) vb->val.bitstring[i]);

    if (status >= buffer_free)
    {
      buffer_ptr += (buffer_free - 1);
      *buffer_ptr = 0;
      return (dst_size + (buffer_free - status));
    }
    else /* if (status < buffer_free) */
    {
      buffer_ptr += status;
      buffer_free -= status;
    }
  }

  return ((int) (dst_size - buffer_free));
}