static counter_list_t *counter_list_search(counter_list_t **list,
                                           unsigned int key) {
  counter_list_t *entry;

  for (entry = *list; entry != NULL; entry = entry->next)
    if (entry->key == key)
      break;

  return (entry);
}