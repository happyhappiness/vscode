void match_destroy(cu_match_t *obj) {
  if (obj == NULL)
    return;

  if ((obj->user_data != NULL) && (obj->free != NULL))
    (*obj->free)(obj->user_data);

  sfree(obj);
}