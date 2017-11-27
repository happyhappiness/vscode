   char *identifier_copy;
   int status;
 
   if ((ret_getval == NULL) || (opts == NULL)) {
     errno = EINVAL;
     cmd_error(CMD_ERROR, err, "Invalid arguments to cmd_parse_getval.");
-    return (CMD_ERROR);
+    return CMD_ERROR;
   }
 
   if (argc != 1) {
     if (argc == 0)
       cmd_error(CMD_PARSE_ERROR, err, "Missing identifier.");
     else
       cmd_error(CMD_PARSE_ERROR, err, "Garbage after identifier: `%s'.",
                 argv[1]);
-    return (CMD_PARSE_ERROR);
+    return CMD_PARSE_ERROR;
   }
 
   /* parse_identifier() modifies its first argument,
    * returning pointers into it */
   identifier_copy = sstrdup(argv[0]);
 
