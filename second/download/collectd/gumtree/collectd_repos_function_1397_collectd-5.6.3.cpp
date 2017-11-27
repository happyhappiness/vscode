int handle_getval(FILE *fh, char *buffer) {
  char *command;
  char *identifier;
  char *identifier_copy;

  char *hostname;
  char *plugin;
  char *plugin_instance;
  char *type;
  char *type_instance;
  gauge_t *values;
  size_t values_num;

  const data_set_t *ds;

  int status;

  if ((fh == NULL) || (buffer == NULL))
    return (-1);

  DEBUG("utils_cmd_getval: handle_getval (fh = %p, buffer = %s);", (void *)fh,
        buffer);

  command = NULL;
  status = parse_string(&buffer, &command);
  if (status != 0) {
    print_to_socket(fh, "-1 Cannot parse command.\n");
    return (-1);
  }
  assert(command != NULL);

  if (strcasecmp("GETVAL", command) != 0) {
    print_to_socket(fh, "-1 Unexpected command: `%s'.\n", command);
    return (-1);
  }

  identifier = NULL;
  status = parse_string(&buffer, &identifier);
  if (status != 0) {
    print_to_socket(fh, "-1 Cannot parse identifier.\n");
    return (-1);
  }
  assert(identifier != NULL);

  if (*buffer != 0) {
    print_to_socket(fh, "-1 Garbage after end of command: %s\n", buffer);
    return (-1);
  }

  /* parse_identifier() modifies its first argument,
   * returning pointers into it */
  identifier_copy = sstrdup(identifier);

  status = parse_identifier(identifier_copy, &hostname, &plugin,
                            &plugin_instance, &type, &type_instance);
  if (status != 0) {
    DEBUG("handle_getval: Cannot parse identifier `%s'.", identifier);
    print_to_socket(fh, "-1 Cannot parse identifier `%s'.\n", identifier);
    sfree(identifier_copy);
    return (-1);
  }

  ds = plugin_get_ds(type);
  if (ds == NULL) {
    DEBUG("handle_getval: plugin_get_ds (%s) == NULL;", type);
    print_to_socket(fh, "-1 Type `%s' is unknown.\n", type);
    sfree(identifier_copy);
    return (-1);
  }

  values = NULL;
  values_num = 0;
  status = uc_get_rate_by_name(identifier, &values, &values_num);
  if (status != 0) {
    print_to_socket(fh, "-1 No such value\n");
    sfree(identifier_copy);
    return (-1);
  }

  if (ds->ds_num != values_num) {
    ERROR("ds[%s]->ds_num = %zu, "
          "but uc_get_rate_by_name returned %zu values.",
          ds->type, ds->ds_num, values_num);
    print_to_socket(fh, "-1 Error reading value from cache.\n");
    sfree(values);
    sfree(identifier_copy);
    return (-1);
  }

  print_to_socket(fh, "%zu Value%s found\n", values_num,
                  (values_num == 1) ? "" : "s");
  for (size_t i = 0; i < values_num; i++) {
    print_to_socket(fh, "%s=", ds->ds[i].name);
    if (isnan(values[i])) {
      print_to_socket(fh, "NaN\n");
    } else {
      print_to_socket(fh, "%12e\n", values[i]);
    }
  }

  sfree(values);
  sfree(identifier_copy);

  return (0);
}