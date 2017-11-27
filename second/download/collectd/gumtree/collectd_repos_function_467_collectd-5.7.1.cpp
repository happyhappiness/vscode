static void mr_free_match(mr_match_t *m) /* {{{ */
{
  if (m == NULL)
    return;

  mr_free_regex(m->host);
  mr_free_regex(m->plugin);
  mr_free_regex(m->plugin_instance);
  mr_free_regex(m->type);
  mr_free_regex(m->type_instance);
  for (llentry_t *e = llist_head(m->meta); e != NULL; e = e->next) {
    sfree(e->key);
    mr_free_regex((mr_regex_t *)e->value);
  }
  llist_destroy(m->meta);

  sfree(m);
}