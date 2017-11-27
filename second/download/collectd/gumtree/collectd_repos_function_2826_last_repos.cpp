static meta_entry_t *md_entry_lookup(meta_data_t *md, /* {{{ */
                                     const char *key) {
  meta_entry_t *e;

  if ((md == NULL) || (key == NULL))
    return NULL;

  for (e = md->head; e != NULL; e = e->next)
    if (strcasecmp(key, e->key) == 0)
      break;

  return e;
}