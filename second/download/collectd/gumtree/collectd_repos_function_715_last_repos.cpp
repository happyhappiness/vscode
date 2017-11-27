static void direct_list_element_free(direct_access_element_t *el) {
  if (el != NULL) {
    DEBUG("onewire plugin: direct_list_element_free - deleting <%s>", el->path);
    sfree(el->path);
    sfree(el->address);
    sfree(el->file);
    free(el);
  }
}