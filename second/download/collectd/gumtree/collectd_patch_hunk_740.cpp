     opt_value = NULL;
     status = cmd_parse_option(argv[i], &opt_key, &opt_value, err);
     if (status != 0) {
       if (status == CMD_NO_OPTION)
         cmd_error(CMD_PARSE_ERROR, err, "Invalid option string `%s'.", argv[i]);
       cmd_destroy_flush(ret_flush);
-      return (CMD_PARSE_ERROR);
+      return CMD_PARSE_ERROR;
     }
 
     if (strcasecmp("plugin", opt_key) == 0) {
       strarray_add(&ret_flush->plugins, &ret_flush->plugins_num, opt_value);
     } else if (strcasecmp("identifier", opt_key) == 0) {
       identifier_t *id =
           realloc(ret_flush->identifiers,
                   (ret_flush->identifiers_num + 1) * sizeof(*id));
       if (id == NULL) {
         cmd_error(CMD_ERROR, err, "realloc failed.");
         cmd_destroy_flush(ret_flush);
-        return (CMD_ERROR);
+        return CMD_ERROR;
       }
 
       ret_flush->identifiers = id;
       id = ret_flush->identifiers + ret_flush->identifiers_num;
       ret_flush->identifiers_num++;
       if (parse_identifier(opt_value, &id->host, &id->plugin,
                            &id->plugin_instance, &id->type, &id->type_instance,
                            opts->identifier_default_host) != 0) {
         cmd_error(CMD_PARSE_ERROR, err, "Invalid identifier `%s'.", opt_value);
         cmd_destroy_flush(ret_flush);
-        return (CMD_PARSE_ERROR);
+        return CMD_PARSE_ERROR;
       }
     } else if (strcasecmp("timeout", opt_key) == 0) {
       char *endptr;
 
       errno = 0;
       endptr = NULL;
