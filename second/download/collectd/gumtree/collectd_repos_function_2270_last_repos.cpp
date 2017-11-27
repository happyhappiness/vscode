cu_tail_t *cu_tail_create(const char *file) {
  cu_tail_t *obj;

  obj = calloc(1, sizeof(*obj));
  if (obj == NULL)
    return NULL;

  obj->file = strdup(file);
  if (obj->file == NULL) {
    free(obj);
    return NULL;
  }

  obj->fh = NULL;

  return obj;
}