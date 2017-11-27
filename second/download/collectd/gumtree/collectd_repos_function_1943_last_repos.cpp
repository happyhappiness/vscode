void *match_get_user_data(cu_match_t *obj) {
  if (obj == NULL)
    return NULL;
  return obj->user_data;
}