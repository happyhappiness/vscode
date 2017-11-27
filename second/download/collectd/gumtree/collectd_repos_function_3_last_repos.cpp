static int cdbi_config_add_database_driver_option(cdbi_database_t *db, /* {{{ */
                                                  oconfig_item_t *ci) {
  cdbi_driver_option_t *option;

  if ((ci->values_num != 2) || (ci->values[0].type != OCONFIG_TYPE_STRING) ||
      ((ci->values[1].type != OCONFIG_TYPE_STRING) &&
       (ci->values[1].type != OCONFIG_TYPE_NUMBER))) {
    WARNING("dbi plugin: The `DriverOption' config option "
            "needs exactly two arguments.");
    return -1;
  }

  option = realloc(db->driver_options,
                   sizeof(*option) * (db->driver_options_num + 1));
  if (option == NULL) {
    ERROR("dbi plugin: realloc failed");
    return -1;
  }

  db->driver_options = option;
  option = db->driver_options + db->driver_options_num;
  memset(option, 0, sizeof(*option));

  option->key = strdup(ci->values[0].value.string);
  if (option->key == NULL) {
    ERROR("dbi plugin: strdup failed.");
    return -1;
  }

  if (ci->values[1].type == OCONFIG_TYPE_STRING) {
    option->value.string = strdup(ci->values[1].value.string);
    if (option->value.string == NULL) {
      ERROR("dbi plugin: strdup failed.");
      sfree(option->key);
      return -1;
    }
  } else {
    assert(ci->values[1].type == OCONFIG_TYPE_NUMBER);
    option->value.numeric = (int)(ci->values[1].value.number + .5);
    option->is_numeric = 1;
  }

  db->driver_options_num++;
  return 0;
}