static yajl_gen_status ovs_yajl_gen_val(yajl_gen jgen, yajl_val jval) {
  size_t array_len = 0;
  yajl_val *jvalues = NULL;
  yajl_val jobj_value = NULL;
  const char *obj_key = NULL;
  size_t obj_len = 0;
  yajl_gen_status yajl_gen_ret = yajl_gen_status_ok;

  if (jval == NULL)
    return yajl_gen_generation_complete;

  if (YAJL_IS_STRING(jval))
    OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, YAJL_GET_STRING(jval));
  else if (YAJL_IS_DOUBLE(jval))
    OVS_YAJL_CALL(yajl_gen_double, jgen, YAJL_GET_DOUBLE(jval));
  else if (YAJL_IS_INTEGER(jval))
    OVS_YAJL_CALL(yajl_gen_double, jgen, YAJL_GET_INTEGER(jval));
  else if (YAJL_IS_TRUE(jval))
    OVS_YAJL_CALL(yajl_gen_bool, jgen, 1);
  else if (YAJL_IS_FALSE(jval))
    OVS_YAJL_CALL(yajl_gen_bool, jgen, 0);
  else if (YAJL_IS_NULL(jval))
    OVS_YAJL_CALL(yajl_gen_null, jgen);
  else if (YAJL_IS_ARRAY(jval)) {
    /* create new array and add all elements into the array */
    array_len = YAJL_GET_ARRAY(jval)->len;
    jvalues = YAJL_GET_ARRAY(jval)->values;
    OVS_YAJL_CALL(yajl_gen_array_open, jgen);
    for (size_t i = 0; i < array_len; i++)
      OVS_YAJL_CALL(ovs_yajl_gen_val, jgen, jvalues[i]);
    OVS_YAJL_CALL(yajl_gen_array_close, jgen);
  } else if (YAJL_IS_OBJECT(jval)) {
    /* create new object and add all elements into the object */
    OVS_YAJL_CALL(yajl_gen_map_open, jgen);
    obj_len = YAJL_GET_OBJECT(jval)->len;
    for (size_t i = 0; i < obj_len; i++) {
      obj_key = YAJL_GET_OBJECT(jval)->keys[i];
      jobj_value = YAJL_GET_OBJECT(jval)->values[i];
      OVS_YAJL_CALL(ovs_yajl_gen_tstring, jgen, obj_key);
      OVS_YAJL_CALL(ovs_yajl_gen_val, jgen, jobj_value);
    }
    OVS_YAJL_CALL(yajl_gen_map_close, jgen);
  } else {
    OVS_ERROR("%s() unsupported value type %d (skip)", __FUNCTION__,
              (int)(jval)->type);
    goto yajl_gen_failure;
  }
  return yajl_gen_status_ok;

yajl_gen_failure:
  OVS_ERROR("%s() error to generate value", __FUNCTION__);
  return yajl_gen_ret;
}