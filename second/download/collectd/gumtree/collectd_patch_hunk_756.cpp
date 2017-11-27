                               cmd_error_handler_t *err) {
   char *key, *value;
 
   if (field == NULL) {
     errno = EINVAL;
     cmd_error(CMD_ERROR, err, "Invalid argument to cmd_parse_option.");
-    return (CMD_ERROR);
+    return CMD_ERROR;
   }
   key = value = field;
 
   /* Look for the equal sign. */
   while (isalnum((int)value[0]) || (value[0] == '_') || (value[0] == ':'))
     value++;
   if ((value[0] != '=') || (value == key)) {
     /* Whether this is a fatal error is up to the caller. */
-    return (CMD_NO_OPTION);
+    return CMD_NO_OPTION;
   }
   *value = '\0';
   value++;
 
   if (ret_key != NULL)
     *ret_key = key;
   if (ret_value != NULL)
     *ret_value = value;
 
-  return (CMD_OK);
+  return CMD_OK;
 } /* cmd_status_t cmd_parse_option */
 
 void cmd_error_fh(void *ud, cmd_status_t status, const char *format,
                   va_list ap) {
   FILE *fh = ud;
   int code = -1;
