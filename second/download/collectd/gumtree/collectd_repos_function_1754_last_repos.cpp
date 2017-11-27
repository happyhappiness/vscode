yajl_val ovs_utils_get_map_value(yajl_val jval, const char *key) {
  size_t map_len = 0;
  size_t array_len = 0;
  yajl_val *map_values = NULL;
  yajl_val *array_values = NULL;
  const char *str_val = NULL;

  /* check YAJL array */
  if (!YAJL_IS_ARRAY(jval) || (key == NULL))
    return NULL;

  /* check a database map value (2-element, first one should be a string */
  array_len = YAJL_GET_ARRAY(jval)->len;
  array_values = YAJL_GET_ARRAY(jval)->values;
  if ((array_len != 2) || (!YAJL_IS_STRING(array_values[0])) ||
      (!YAJL_IS_ARRAY(array_values[1])))
    return NULL;

  /* check first element of the array */
  str_val = YAJL_GET_STRING(array_values[0]);
  if (strcmp("map", str_val) != 0)
    return NULL;

  /* try to find map value by map key */
  map_len = YAJL_GET_ARRAY(array_values[1])->len;
  map_values = YAJL_GET_ARRAY(array_values[1])->values;
  for (size_t i = 0; i < map_len; i++) {
    /* check YAJL array */
    if (!YAJL_IS_ARRAY(map_values[i]))
      break;

    /* check a database pair value (2-element, first one represents a key
     * and it should be a string in our case */
    array_len = YAJL_GET_ARRAY(map_values[i])->len;
    array_values = YAJL_GET_ARRAY(map_values[i])->values;
    if ((array_len != 2) || (!YAJL_IS_STRING(array_values[0])))
      break;

    /* return map value if given key equals map key */
    str_val = YAJL_GET_STRING(array_values[0]);
    if (strcmp(key, str_val) == 0)
      return array_values[1];
  }
  return NULL;
}