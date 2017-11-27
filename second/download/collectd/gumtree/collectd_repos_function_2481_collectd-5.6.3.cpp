static cf_callback_t *cf_search(const char *type) {
  cf_callback_t *cf_cb;

  if (type == NULL)
    return (NULL);

  for (cf_cb = first_callback; cf_cb != NULL; cf_cb = cf_cb->next)
    if (strcasecmp(cf_cb->type, type) == 0)
      break;

  return (cf_cb);
}