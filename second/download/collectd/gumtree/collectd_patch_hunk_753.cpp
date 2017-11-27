       /* Outside of quotes, a backslash is a regular character (mostly
        * for backward compatibility). */
 
       if (string[1] == '\0') {
         free(fields);
         cmd_error(CMD_PARSE_ERROR, err, "Backslash at end of string.");
-        return (CMD_PARSE_ERROR);
+        return CMD_PARSE_ERROR;
       }
 
       /* un-escape the next character; skip backslash */
       string++;
     }
 
