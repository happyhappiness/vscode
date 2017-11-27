static void snmp_agent_free_table(table_definition_t **td) {

  if (td == NULL || *td == NULL)
    return;

  if ((*td)->size_oid.oid_len)
    unregister_mib((*td)->size_oid.oid, (*td)->size_oid.oid_len);

  /* Unregister Index OIDs */
  if ((*td)->index_oid.oid_len) {
    int *index;
    char *instance;

    c_avl_iterator_t *iter = c_avl_get_iterator((*td)->index_instance);
    while (c_avl_iterator_next(iter, (void *)&index, (void *)&instance) == 0)
      snmp_agent_unregister_oid_index(&(*td)->index_oid, *index);

    c_avl_iterator_destroy(iter);
  }

  /* Unregister all table columns and their registered OIDs */
  snmp_agent_free_table_columns(*td);

  void *key = NULL;
  void *value = NULL;

  /* index_instance and instance_index contain the same pointers */
  c_avl_destroy((*td)->index_instance);
  (*td)->index_instance = NULL;

  if ((*td)->instance_index != NULL) {
    while (c_avl_pick((*td)->instance_index, &key, &value) == 0) {
      if (key != value)
        sfree(key);
      sfree(value);
    }
    c_avl_destroy((*td)->instance_index);
    (*td)->instance_index = NULL;
  }

  sfree((*td)->name);
  sfree(*td);

  return;
}