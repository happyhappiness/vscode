static int fc_config_set_instance(fc_directory_conf_t *dir, const char *str) {
  char buffer[1024];
  char *ptr;
  char *copy;

  sstrncpy(buffer, str, sizeof(buffer));
  for (ptr = buffer; *ptr != 0; ptr++)
    if (*ptr == '/')
      *ptr = '_';

  for (ptr = buffer; *ptr == '_'; ptr++)
    /* do nothing */;

  if (*ptr == 0)
    return (-1);

  copy = strdup(ptr);
  if (copy == NULL)
    return (-1);

  sfree(dir->instance);
  dir->instance = copy;

  return (0);
}