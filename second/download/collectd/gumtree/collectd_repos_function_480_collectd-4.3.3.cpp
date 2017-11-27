static int parse_message (notification_t *n, char **fields, int fields_num)
{
  int status;

  /* Strip off the leading `message=' */
  fields[0] += strlen ("message=");

  status = strjoin (n->message, sizeof (n->message), fields, fields_num, " ");
  if (status < 0)
    return (-1);

  return (0);
}