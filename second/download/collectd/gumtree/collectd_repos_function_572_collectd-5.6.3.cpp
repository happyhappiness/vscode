int parse_option(char **ret_buffer, char **ret_key, char **ret_value) {
  char *buffer;
  char *key;
  char *value;
  int status;

  buffer = *ret_buffer;

  /* Eat up leading spaces */
  key = buffer;
  while (isspace((int)*key))
    key++;
  if (*key == 0)
    return (1);

  /* Look for the equal sign */
  buffer = key;
  while (isalnum((int)*buffer) || *buffer == '_' || *buffer == ':')
    buffer++;
  if ((*buffer != '=') || (buffer == key))
    return (1);
  *buffer = 0;
  buffer++;
  /* Empty values must be written as "" */
  if (isspace((int)*buffer) || (*buffer == 0))
    return (-1);

  status = parse_string(&buffer, &value);
  if (status != 0)
    return (-1);

  /* NB: parse_string will have eaten up all trailing spaces. */

  *ret_buffer = buffer;
  *ret_key = key;
  *ret_value = value;

  return (0);
}