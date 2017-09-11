@@ -1310,7 +1310,7 @@ struct rewriteConfigState *rewriteConfigReadOldFile(char *path) {
  * "force" is non-zero, the line is appended to the configuration file.
  * Usually "force" is true when an option has not its default value, so it
  * must be rewritten even if not present previously.
- * 
+ *
  * The first time a line is appended into a configuration file, a comment
  * is added to show that starting from that point the config file was generated
  * by CONFIG REWRITE.
@@ -1436,7 +1436,7 @@ void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int
     char *enum_name, *matching_name = NULL;
     int enum_val, def_val, force;
     sds line;
-    
+
     va_start(ap, value);
     while(1) {
         enum_name = va_arg(ap,char*);
@@ -1448,7 +1448,7 @@ void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int
         if (value == enum_val) matching_name = enum_name;
     }
     va_end(ap);
-    
+
     force = value != def_val;
     line = sdscatprintf(sdsempty(),"%s %s",option,matching_name);
     rewriteConfigRewriteLine(state,option,line,force);