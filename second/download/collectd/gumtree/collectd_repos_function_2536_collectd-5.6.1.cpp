int rfc3339nano (char *buffer, size_t buffer_size, cdtime_t t) /* {{{ */
{
  if (buffer_size < RFC3339NANO_SIZE)
    return ENOMEM;

  return format_rfc3339 (buffer, buffer_size, t, 1);
}