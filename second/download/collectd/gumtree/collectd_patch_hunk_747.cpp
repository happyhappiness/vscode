   const data_set_t *ds;
   value_list_t vl = VALUE_LIST_INIT;
 
   if ((ret_putval == NULL) || (opts == NULL)) {
     errno = EINVAL;
     cmd_error(CMD_ERROR, err, "Invalid arguments to cmd_parse_putval.");
-    return (CMD_ERROR);
+    return CMD_ERROR;
   }
 
   if (argc < 2) {
     cmd_error(CMD_PARSE_ERROR, err, "Missing identifier and/or value-list.");
-    return (CMD_PARSE_ERROR);
+    return CMD_PARSE_ERROR;
   }
 
   identifier = argv[0];
 
   /* parse_identifier() modifies its first argument, returning pointers into
    * it; retain the old value for later. */
