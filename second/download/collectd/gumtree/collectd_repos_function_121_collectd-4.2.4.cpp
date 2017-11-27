static int parse_line (char *buffer)
{
  char *fields[256];
  int fields_num;

  fields[0] = "PUTVAL";
  fields_num = strsplit (buffer, &fields[1], STATIC_ARRAY_SIZE(fields) - 1);

  handle_putval (stdout, fields, fields_num + 1);
  return (0);
}