static int parse_line (char *buffer) /* {{{ */
{
  char *fields[256];
  int fields_num;

  fields[0] = "PUTVAL";
  fields_num = strsplit (buffer, fields + 1, STATIC_ARRAY_SIZE(fields) - 1);

  if (strcasecmp (fields[1], "putval") == 0)
    return (handle_putval (stdout, fields + 1, fields_num));
  else if (strcasecmp (fields[1], "putnotif") == 0)
    return (handle_putnotif (stdout, fields + 1, fields_num));

  /* compatibility code */
  return (handle_putval (stdout, fields, fields_num + 1));
}