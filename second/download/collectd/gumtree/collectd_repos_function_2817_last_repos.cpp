int rfc3339_local(char *buffer, size_t buffer_size, cdtime_t t) /* {{{ */
{
  if (buffer_size < RFC3339_SIZE)
    return ENOMEM;

  return format_rfc3339_local(buffer, buffer_size, t, 0);
}