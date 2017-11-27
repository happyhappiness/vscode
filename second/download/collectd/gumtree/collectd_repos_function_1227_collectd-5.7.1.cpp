static char *strip_prefix(char *topic) {
  size_t num = 0;

  for (size_t i = 0; topic[i] != 0; i++)
    if (topic[i] == '/')
      num++;

  if (num < 2)
    return (NULL);

  while (num > 2) {
    char *tmp = strchr(topic, '/');
    if (tmp == NULL)
      return (NULL);
    topic = tmp + 1;
    num--;
  }

  return (topic);
}