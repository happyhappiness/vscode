static char *values_type_to_sqlarray(const data_set_t *ds, char *string,
                                     size_t string_len, _Bool store_rates) {
  char *str_ptr;
  size_t str_len;

  str_ptr = string;
  str_len = string_len;

  for (size_t i = 0; i < ds->ds_num; ++i) {
    int status;

    if (store_rates)
      status = ssnprintf(str_ptr, str_len, ",'gauge'");
    else
      status = ssnprintf(str_ptr, str_len, ",'%s'",
                         DS_TYPE_TO_STRING(ds->ds[i].type));

    if (status < 1) {
      str_len = 0;
      break;
    } else if ((size_t)status >= str_len) {
      str_len = 0;
      break;
    } else {
      str_ptr += status;
      str_len -= (size_t)status;
    }
  }

  if (str_len <= 2) {
    log_err("c_psql_write: Failed to stringify value types");
    return NULL;
  }

  /* overwrite the first comma */
  string[0] = '{';
  str_ptr[0] = '}';
  str_ptr[1] = '\0';

  return string;
}