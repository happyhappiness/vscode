static inline void ignorelist_append(ignorelist_t *il,
                                     ignorelist_item_t *item) {
  assert((il != NULL) && (item != NULL));

  item->next = il->head;
  il->head = item;
}