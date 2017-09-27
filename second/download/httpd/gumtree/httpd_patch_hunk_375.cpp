          */
         new->real = r;
     }
     new->fake = f;
     new->handler = cmd->info;
 
+    /* check for overlapping (Script)Alias directives
+     * and throw a warning if found one
+     */
+    if (!use_regex) {
+        for (i = 0; i < conf->aliases->nelts - 1; ++i) {
+            alias_entry *p = &entries[i];
+
+            if (  (!p->regexp &&  alias_matches(f, p->fake) > 0)
+                || (p->regexp && !ap_regexec(p->regexp, f, 0, NULL, 0))) {
+                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
+                             "The %s directive in %s at line %d will probably "
+                             "never match because it overlaps an earlier "
+                             "%sAlias%s.",
+                             cmd->cmd->name, cmd->directive->filename,
+                             cmd->directive->line_num,
+                             p->handler ? "Script" : "",
+                             p->regexp ? "Match" : "");
+
+                break; /* one warning per alias should be sufficient */
+            }
+        }
+    }
+
     return NULL;
 }
 
 static const char *add_alias(cmd_parms *cmd, void *dummy, const char *f,
                              const char *r)
 {
