void ignorelist_set_invert(ignorelist_t *il, int invert) {
  if (il == NULL) {
    DEBUG("ignore call with ignorelist_t == NULL");
    return;
  }

  il->ignore = invert ? 0 : 1;
}