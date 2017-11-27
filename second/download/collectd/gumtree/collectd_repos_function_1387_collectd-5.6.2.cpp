static void counter_list_add(counter_list_t **list, unsigned int key,
                             unsigned int increment) {
  counter_list_t *entry;

  entry = counter_list_search(list, key);

  if (entry != NULL) {
    entry->value += increment;
  } else {
    counter_list_create(list, key, increment);
  }
}