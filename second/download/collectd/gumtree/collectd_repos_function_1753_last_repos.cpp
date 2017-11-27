yajl_val ovs_utils_get_value_by_key(yajl_val jval, const char *key) {
  const char *obj_key = NULL;

  /* check params */
  if (!YAJL_IS_OBJECT(jval) || (key == NULL))
    return NULL;

  /* find a value by key */
  for (size_t i = 0; i < YAJL_GET_OBJECT(jval)->len; i++) {
    obj_key = YAJL_GET_OBJECT(jval)->keys[i];
    if (strcmp(obj_key, key) == 0)
      return YAJL_GET_OBJECT(jval)->values[i];
  }

  return NULL;
}