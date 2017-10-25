static char *my_get_token(const char *line)
{
  static const char *save = NULL;
  const char *first = NULL;
  const char *last = NULL;
  char *retval = NULL;
  size_t size;

  if (NULL == line)
    line = save;
  if (NULL == line)
    return NULL;

  while (('\0' != *line) && (isspace(*line)))
    line++;
  first = line;
  while (('\0' != *line) && (!isspace(*line)))
    line++;
  save = line;
  while ('\0' != *line)
    line++;
  last = line;

  size = last - first;
  if (0 == size)
    return NULL;
  if (NULL == (retval = malloc(size + 1)))
    return NULL;
  memcpy(retval, first, size);
  retval[size] = '\0';
  return retval;
}