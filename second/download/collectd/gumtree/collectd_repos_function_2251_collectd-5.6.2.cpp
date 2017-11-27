void oconfig_free(oconfig_item_t *ci) {
  oconfig_free_all(ci);
  free(ci);
}