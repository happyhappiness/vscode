int parse_string (char **ret_buffer, char **ret_string)
{
  char *buffer;
  char *string;

  buffer = *ret_buffer;

  /* Eat up leading spaces. */
  string = buffer;
  while (isspace ((int) *string))
    string++;
  if (*string == 0)
    return (1);

  /* A quoted string */
  if (*string == '"')
  {
    char *dst;

    string++;
    if (*string == 0)
      return (1);

    dst = string;
    buffer = string;
    while ((*buffer != '"') && (*buffer != 0))
    {
      /* Un-escape backslashes */
      if (*buffer == '\\')
      {
        buffer++;
        /* Catch a backslash at the end of buffer */
        if (*buffer == 0)
          return (-1);
      }
      *dst = *buffer;
      buffer++;
      dst++;
    }
    /* No quote sign has been found */
    if (*buffer == 0)
      return (-1);

    *dst = 0;
    dst++;
    *buffer = 0;
    buffer++;

    /* Check for trailing spaces. */
    if ((*buffer != 0) && !isspace ((int) *buffer))
      return (-1);
  }
  else /* an unquoted string */
  {
    buffer = string;
    while ((*buffer != 0) && !isspace ((int) *buffer))
      buffer++;
    if (*buffer != 0)
    {
      *buffer = 0;
      buffer++;
    }
  }

  /* Eat up trailing spaces */
  while (isspace ((int) *buffer))
    buffer++;

  *ret_buffer = buffer;
  *ret_string = string;

  return (0);
}