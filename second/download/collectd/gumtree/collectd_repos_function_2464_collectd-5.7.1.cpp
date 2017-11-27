static int ignorelist_match_string(ignorelist_item_t *item, const char *entry) {
  assert((item != NULL) && (item->smatch != NULL) && (entry != NULL) &&
         (strlen(entry) > 0));

  if (strcmp(entry, item->smatch) == 0)
    return (1);

  return (0);
}