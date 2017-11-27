static int parse_option_time (notification_t *n, char *value)
{
  time_t tmp;
  
  tmp = (time_t) atoi (value);
  if (tmp <= 0)
    return (-1);

  n->time = tmp;

  return (0);
}