     if ((errno == 0) && (endptr != NULL) && (endptr != value) && (tmp > 0.0))
       vl->interval = DOUBLE_TO_CDTIME_T(tmp);
   } else
     return (1);
 
   return (0);
-} /* int parse_option */
+} /* int set_option */
+
+/*
+ * public API
+ */
+
+cmd_status_t cmd_parse_putval(size_t argc, char **argv,
+                              cmd_putval_t *ret_putval,
+                              const cmd_options_t *opts,
+                              cmd_error_handler_t *err) {
+  cmd_status_t result;
 
-int handle_putval(FILE *fh, char *buffer) {
-  char *command;
   char *identifier;
   char *hostname;
   char *plugin;
   char *plugin_instance;
   char *type;
   char *type_instance;
   int status;
-  int values_submitted;
 
   char *identifier_copy;
 
   const data_set_t *ds;
   value_list_t vl = VALUE_LIST_INIT;
-  vl.values = NULL;
-
-  DEBUG("utils_cmd_putval: handle_putval (fh = %p, buffer = %s);", (void *)fh,
-        buffer);
 
-  command = NULL;
-  status = parse_string(&buffer, &command);
-  if (status != 0) {
-    print_to_socket(fh, "-1 Cannot parse command.\n");
-    return (-1);
+  if ((ret_putval == NULL) || (opts == NULL)) {
+    errno = EINVAL;
+    cmd_error(CMD_ERROR, err, "Invalid arguments to cmd_parse_putval.");
+    return (CMD_ERROR);
   }
-  assert(command != NULL);
 
-  if (strcasecmp("PUTVAL", command) != 0) {
-    print_to_socket(fh, "-1 Unexpected command: `%s'.\n", command);
-    return (-1);
+  if (argc < 2) {
+    cmd_error(CMD_PARSE_ERROR, err, "Missing identifier and/or value-list.");
+    return (CMD_PARSE_ERROR);
   }
 
-  identifier = NULL;
-  status = parse_string(&buffer, &identifier);
-  if (status != 0) {
-    print_to_socket(fh, "-1 Cannot parse identifier.\n");
-    return (-1);
-  }
-  assert(identifier != NULL);
+  identifier = argv[0];
 
-  /* parse_identifier() modifies its first argument,
-   * returning pointers into it */
+  /* parse_identifier() modifies its first argument, returning pointers into
+   * it; retain the old value for later. */
   identifier_copy = sstrdup(identifier);
 
-  status = parse_identifier(identifier_copy, &hostname, &plugin,
-                            &plugin_instance, &type, &type_instance);
+  status =
+      parse_identifier(identifier, &hostname, &plugin, &plugin_instance, &type,
+                       &type_instance, opts->identifier_default_host);
   if (status != 0) {
-    DEBUG("handle_putval: Cannot parse identifier `%s'.", identifier);
-    print_to_socket(fh, "-1 Cannot parse identifier `%s'.\n", identifier);
+    DEBUG("cmd_handle_putval: Cannot parse identifier `%s'.", identifier_copy);
+    cmd_error(CMD_PARSE_ERROR, err, "Cannot parse identifier `%s'.",
+              identifier_copy);
     sfree(identifier_copy);
-    return (-1);
+    return (CMD_PARSE_ERROR);
   }
 
   if ((strlen(hostname) >= sizeof(vl.host)) ||
       (strlen(plugin) >= sizeof(vl.plugin)) ||
       ((plugin_instance != NULL) &&
        (strlen(plugin_instance) >= sizeof(vl.plugin_instance))) ||
       ((type_instance != NULL) &&
        (strlen(type_instance) >= sizeof(vl.type_instance)))) {
-    print_to_socket(fh, "-1 Identifier too long.\n");
+    cmd_error(CMD_PARSE_ERROR, err, "Identifier too long.");
     sfree(identifier_copy);
-    return (-1);
+    return (CMD_PARSE_ERROR);
   }
 
   sstrncpy(vl.host, hostname, sizeof(vl.host));
   sstrncpy(vl.plugin, plugin, sizeof(vl.plugin));
   sstrncpy(vl.type, type, sizeof(vl.type));
   if (plugin_instance != NULL)
     sstrncpy(vl.plugin_instance, plugin_instance, sizeof(vl.plugin_instance));
   if (type_instance != NULL)
     sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));
 
   ds = plugin_get_ds(type);
   if (ds == NULL) {
-    print_to_socket(fh, "-1 Type `%s' isn't defined.\n", type);
+    cmd_error(CMD_PARSE_ERROR, err, "1 Type `%s' isn't defined.", type);
     sfree(identifier_copy);
-    return (-1);
+    return (CMD_PARSE_ERROR);
   }
 
-  /* Free identifier_copy */
   hostname = NULL;
   plugin = NULL;
   plugin_instance = NULL;
   type = NULL;
   type_instance = NULL;
-  sfree(identifier_copy);
 
   vl.values_len = ds->ds_num;
   vl.values = malloc(vl.values_len * sizeof(*vl.values));
   if (vl.values == NULL) {
-    print_to_socket(fh, "-1 malloc failed.\n");
-    return (-1);
+    cmd_error(CMD_ERROR, err, "malloc failed.");
+    sfree(identifier_copy);
+    return (CMD_ERROR);
+  }
+
+  ret_putval->raw_identifier = identifier_copy;
+  if (ret_putval->raw_identifier == NULL) {
+    cmd_error(CMD_ERROR, err, "malloc failed.");
+    cmd_destroy_putval(ret_putval);
+    sfree(vl.values);
+    return (CMD_ERROR);
   }
 
-  /* All the remaining fields are part of the optionlist. */
-  values_submitted = 0;
-  while (*buffer != 0) {
-    char *string = NULL;
+  /* All the remaining fields are part of the option list. */
+  result = CMD_OK;
+  for (size_t i = 1; i < argc; ++i) {
+    value_list_t *tmp;
+
+    char *key = NULL;
     char *value = NULL;
 
-    status = parse_option(&buffer, &string, &value);
-    if (status < 0) {
-      /* parse_option failed, buffer has been modified.
-       * => we need to abort */
-      print_to_socket(fh, "-1 Misformatted option.\n");
-      sfree(vl.values);
-      return (-1);
-    } else if (status == 0) {
-      assert(string != NULL);
+    status = cmd_parse_option(argv[i], &key, &value, err);
+    if (status == CMD_OK) {
+      assert(key != NULL);
       assert(value != NULL);
-      set_option(&vl, string, value);
+      set_option(&vl, key, value);
       continue;
+    } else if (status != CMD_NO_OPTION) {
+      /* parse_option failed, buffer has been modified.
+       * => we need to abort */
+      result = status;
+      break;
     }
-    /* else: parse_option but buffer has not been modified. This is
-     * the default if no `=' is found.. */
+    /* else: cmd_parse_option did not find an option; treat this as a
+     * value list. */
 
-    status = parse_string(&buffer, &string);
+    status = parse_values(argv[i], &vl, ds);
     if (status != 0) {
-      print_to_socket(fh, "-1 Misformatted value.\n");
-      sfree(vl.values);
-      return (-1);
+      cmd_error(CMD_PARSE_ERROR, err, "Parsing the values string failed.");
+      result = CMD_PARSE_ERROR;
+      break;
     }
-    assert(string != NULL);
 
-    status = parse_values(string, &vl, ds);
-    if (status != 0) {
-      print_to_socket(fh, "-1 Parsing the values string failed.\n");
-      sfree(vl.values);
-      return (-1);
+    tmp = (value_list_t *)realloc(ret_putval->vl, (ret_putval->vl_num + 1) *
+                                                      sizeof(*ret_putval->vl));
+    if (tmp == NULL) {
+      cmd_error(CMD_ERROR, err, "realloc failed.");
+      cmd_destroy_putval(ret_putval);
+      result = CMD_ERROR;
+      break;
     }
 
-    plugin_dispatch_values(&vl);
-    values_submitted++;
+    ret_putval->vl = tmp;
+    ret_putval->vl_num++;
+    memcpy(&ret_putval->vl[ret_putval->vl_num - 1], &vl, sizeof(vl));
   } /* while (*buffer != 0) */
   /* Done parsing the options. */
 
-  if (fh != stdout)
-    print_to_socket(fh, "0 Success: %i %s been dispatched.\n", values_submitted,
-                    (values_submitted == 1) ? "value has" : "values have");
+  if (result != CMD_OK) {
+    if (ret_putval->vl_num == 0)
+      sfree(vl.values);
+    cmd_destroy_putval(ret_putval);
+  }
 
-  sfree(vl.values);
-  return (0);
-} /* int handle_putval */
+  return (result);
+} /* cmd_status_t cmd_parse_putval */
+
+void cmd_destroy_putval(cmd_putval_t *putval) {
+  if (putval == NULL)
+    return;
+
+  sfree(putval->raw_identifier);
+
+  for (size_t i = 0; i < putval->vl_num; ++i) {
+    if (i == 0) /* values is shared between all entries */
+      sfree(putval->vl[i].values);
+    meta_data_destroy(putval->vl[i].meta);
+    putval->vl[i].meta = NULL;
+  }
+  sfree(putval->vl);
+  putval->vl = NULL;
+  putval->vl_num = 0;
+} /* void cmd_destroy_putval */
+
+cmd_status_t cmd_handle_putval(FILE *fh, char *buffer) {
+  cmd_error_handler_t err = {cmd_error_fh, fh};
+  cmd_t cmd;
+
+  int status;
+
+  DEBUG("utils_cmd_putval: cmd_handle_putval (fh = %p, buffer = %s);",
+        (void *)fh, buffer);
+
+  if ((status = cmd_parse(buffer, &cmd, NULL, &err)) != CMD_OK)
+    return (status);
+  if (cmd.type != CMD_PUTVAL) {
+    cmd_error(CMD_UNKNOWN_COMMAND, &err, "Unexpected command: `%s'.",
+              CMD_TO_STRING(cmd.type));
+    cmd_destroy(&cmd);
+    return (CMD_UNKNOWN_COMMAND);
+  }
+
+  for (size_t i = 0; i < cmd.cmd.putval.vl_num; ++i)
+    plugin_dispatch_values(&cmd.cmd.putval.vl[i]);
+
+  if (fh != stdout)
+    cmd_error(CMD_OK, &err, "Success: %i %s been dispatched.",
+              (int)cmd.cmd.putval.vl_num,
+              (cmd.cmd.putval.vl_num == 1) ? "value has" : "values have");
+
+  cmd_destroy(&cmd);
+  return (CMD_OK);
+} /* int cmd_handle_putval */
 
-int create_putval(char *ret, size_t ret_len, /* {{{ */
-                  const data_set_t *ds, const value_list_t *vl) {
+int cmd_create_putval(char *ret, size_t ret_len, /* {{{ */
+                      const data_set_t *ds, const value_list_t *vl) {
   char buffer_ident[6 * DATA_MAX_NAME_LEN];
   char buffer_values[1024];
   int status;
 
   status = FORMAT_VL(buffer_ident, sizeof(buffer_ident), vl);
   if (status != 0)
