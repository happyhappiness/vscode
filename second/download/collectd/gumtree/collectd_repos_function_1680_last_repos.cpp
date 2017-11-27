static void snmp_agent_free_table_columns(table_definition_t *td) {
  if (td->columns == NULL)
    return;

  for (llentry_t *de = llist_head(td->columns); de != NULL; de = de->next) {
    data_definition_t *dd = de->value;

    if (td->index_oid.oid_len) {
      int *index;
      char *instance;

      c_avl_iterator_t *iter = c_avl_get_iterator(td->index_instance);
      while (c_avl_iterator_next(iter, (void *)&index, (void *)&instance) ==
             0) {
        for (size_t i = 0; i < dd->oids_len; i++)
          snmp_agent_unregister_oid_index(&dd->oids[i], *index);
      }
      c_avl_iterator_destroy(iter);
    } else {
      char *instance;

      c_avl_iterator_t *iter = c_avl_get_iterator(dd->table->instance_index);
      while (c_avl_iterator_next(iter, (void *)&instance, (void *)&instance) ==
             0) {
        for (size_t i = 0; i < dd->oids_len; i++)
          snmp_agent_unregister_oid_string(&dd->oids[i], instance);
      }
      c_avl_iterator_destroy(iter);
    }

    snmp_agent_free_data(&dd);
  }

  llist_destroy(td->columns);
  td->columns = NULL;
}