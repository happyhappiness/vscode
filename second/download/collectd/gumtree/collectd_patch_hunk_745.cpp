                                const cmd_options_t *opts
                                __attribute__((unused)),
                                cmd_error_handler_t *err) {
   if (argc != 0) {
     cmd_error(CMD_PARSE_ERROR, err, "Garbage after end of command: `%s'.",
               argv[0]);
-    return (CMD_PARSE_ERROR);
+    return CMD_PARSE_ERROR;
   }
 
-  return (CMD_OK);
+  return CMD_OK;
 } /* cmd_status_t cmd_parse_listval */
 
 #define free_everything_and_return(status)                                     \
   do {                                                                         \
     for (size_t j = 0; j < number; j++) {                                      \
       sfree(names[j]);                                                         \
       names[j] = NULL;                                                         \
     }                                                                          \
     sfree(names);                                                              \
     sfree(times);                                                              \
-    return (status);                                                           \
+    return status;                                                             \
   } while (0)
 
 #define print_to_socket(fh, ...)                                               \
   do {                                                                         \
     if (fprintf(fh, __VA_ARGS__) < 0) {                                        \
       char errbuf[1024];                                                       \
