       &ret_getval->identifier.type_instance, opts->identifier_default_host);
   if (status != 0) {
     DEBUG("cmd_parse_getval: Cannot parse identifier `%s'.", identifier_copy);
     cmd_error(CMD_PARSE_ERROR, err, "Cannot parse identifier `%s'.",
               identifier_copy);
     sfree(identifier_copy);
-    return (CMD_PARSE_ERROR);
+    return CMD_PARSE_ERROR;
   }
 
   ret_getval->raw_identifier = identifier_copy;
-  return (CMD_OK);
+  return CMD_OK;
 } /* cmd_status_t cmd_parse_getval */
 
 #define print_to_socket(fh, ...)                                               \
   do {                                                                         \
     if (fprintf(fh, __VA_ARGS__) < 0) {                                        \
       char errbuf[1024];                                                       \
