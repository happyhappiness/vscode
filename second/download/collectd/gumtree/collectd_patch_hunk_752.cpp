   }
 
   /* fields will be NULL-terminated */
   fields = malloc((estimate + 1) * sizeof(*fields));
   if (fields == NULL) {
     cmd_error(CMD_ERROR, err, "malloc failed.");
-    return (CMD_ERROR);
+    return CMD_ERROR;
   }
 
 #define END_FIELD()                                                            \
   do {                                                                         \
     *field = '\0';                                                             \
     field = NULL;                                                              \
