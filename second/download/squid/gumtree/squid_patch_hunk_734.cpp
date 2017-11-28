         storeAppendPrintf(entry, "%s %s\n", name, var);
 }
 
 static void
 parse_string(char **var)
 {
-    char *token = strtok(NULL, w_space);
+    char *token = ConfigParser::NextToken();
     safe_free(*var);
 
     if (token == NULL)
         self_destruct();
 
     *var = xstrdup(token);
 }
 
-void
-ConfigParser::ParseString(char **var)
-{
-    parse_string(var);
-}
-
-void
-ConfigParser::ParseString(String *var)
-{
-    char *token = strtok(NULL, w_space);
-
-    if (token == NULL)
-        self_destruct();
-
-    var->reset(token);
-}
-
 static void
 free_string(char **var)
 {
     safe_free(*var);
 }
 
