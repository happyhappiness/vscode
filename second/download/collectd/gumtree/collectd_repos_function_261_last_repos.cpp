ignorelist_t *ignorelist_create(int invert) {
  ignorelist_t *il;

  il = calloc(1, sizeof(*il));
  if (il == NULL)
    return NULL;

  /*
   * ->ignore == 0  =>  collect
   * ->ignore == 1  =>  ignore
   */
  il->ignore = invert ? 0 : 1;

  return il;
}