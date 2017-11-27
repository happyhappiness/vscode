static int format_time(yajl_gen g, cdtime_t t) /* {{{ */
{
  char buffer[RFC3339NANO_SIZE] = "";

  if (rfc3339nano(buffer, sizeof(buffer), t) != 0)
    return -1;

  JSON_ADD(g, buffer);
  return 0;
}