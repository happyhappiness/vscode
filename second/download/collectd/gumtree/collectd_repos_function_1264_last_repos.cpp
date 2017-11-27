static bson_t *wm_create_bson(const data_set_t *ds, /* {{{ */
                              const value_list_t *vl, _Bool store_rates) {
  bson_t *ret;
  bson_t subarray;
  gauge_t *rates;

  ret = bson_new();
  if (!ret) {
    ERROR("write_mongodb plugin: bson_new failed.");
    return NULL;
  }

  if (store_rates) {
    rates = uc_get_rate(ds, vl);
    if (rates == NULL) {
      ERROR("write_mongodb plugin: uc_get_rate() failed.");
      bson_destroy(ret);
      return NULL;
    }
  } else {
    rates = NULL;
  }

  BSON_APPEND_DATE_TIME(ret, "timestamp", CDTIME_T_TO_MS(vl->time));
  BSON_APPEND_UTF8(ret, "host", vl->host);
  BSON_APPEND_UTF8(ret, "plugin", vl->plugin);
  BSON_APPEND_UTF8(ret, "plugin_instance", vl->plugin_instance);
  BSON_APPEND_UTF8(ret, "type", vl->type);
  BSON_APPEND_UTF8(ret, "type_instance", vl->type_instance);

  BSON_APPEND_ARRAY_BEGIN(ret, "values", &subarray); /* {{{ */
  for (size_t i = 0; i < ds->ds_num; i++) {
    char key[16];

    snprintf(key, sizeof(key), "%zu", i);

    if (ds->ds[i].type == DS_TYPE_GAUGE)
      BSON_APPEND_DOUBLE(&subarray, key, vl->values[i].gauge);
    else if (store_rates)
      BSON_APPEND_DOUBLE(&subarray, key, (double)rates[i]);
    else if (ds->ds[i].type == DS_TYPE_COUNTER)
      BSON_APPEND_INT64(&subarray, key, vl->values[i].counter);
    else if (ds->ds[i].type == DS_TYPE_DERIVE)
      BSON_APPEND_INT64(&subarray, key, vl->values[i].derive);
    else if (ds->ds[i].type == DS_TYPE_ABSOLUTE)
      BSON_APPEND_INT64(&subarray, key, vl->values[i].absolute);
    else {
      ERROR("write_mongodb plugin: Unknown ds_type %d for index %zu",
            ds->ds[i].type, i);
      bson_destroy(ret);
      return NULL;
    }
  }
  bson_append_array_end(ret, &subarray); /* }}} values */

  BSON_APPEND_ARRAY_BEGIN(ret, "dstypes", &subarray); /* {{{ */
  for (size_t i = 0; i < ds->ds_num; i++) {
    char key[16];

    snprintf(key, sizeof(key), "%zu", i);

    if (store_rates)
      BSON_APPEND_UTF8(&subarray, key, "gauge");
    else
      BSON_APPEND_UTF8(&subarray, key, DS_TYPE_TO_STRING(ds->ds[i].type));
  }
  bson_append_array_end(ret, &subarray); /* }}} dstypes */

  BSON_APPEND_ARRAY_BEGIN(ret, "dsnames", &subarray); /* {{{ */
  for (size_t i = 0; i < ds->ds_num; i++) {
    char key[16];

    snprintf(key, sizeof(key), "%zu", i);
    BSON_APPEND_UTF8(&subarray, key, ds->ds[i].name);
  }
  bson_append_array_end(ret, &subarray); /* }}} dsnames */

  sfree(rates);

  size_t error_location;
  if (!bson_validate(ret, BSON_VALIDATE_UTF8, &error_location)) {
    ERROR("write_mongodb plugin: Error in generated BSON document "
          "at byte %zu",
          error_location);
    bson_destroy(ret);
    return NULL;
  }

  return ret;
}