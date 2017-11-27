static mb_data_t *data_get_by_name(mb_data_t *src, /* {{{ */
                                   const char *name) {
  if (name == NULL)
    return (NULL);

  for (mb_data_t *ptr = src; ptr != NULL; ptr = ptr->next)
    if (strcasecmp(ptr->name, name) == 0)
      return (ptr);

  return (NULL);
}