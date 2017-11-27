static void mcelog_free_dimms_list_records(llist_t *dimms_list) {

  for (llentry_t *e = llist_head(dimms_list); e != NULL; e = e->next) {
    sfree(e->key);
    sfree(e->value);
  }
}