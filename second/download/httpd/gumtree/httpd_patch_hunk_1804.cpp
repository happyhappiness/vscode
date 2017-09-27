         }
     }
 
     return NULL;
 }
 
+static const char *set_default_type(cmd_parms *cmd, void *d_,
+                                   const char *arg)
+{
+    if ((strcasecmp(arg, "off") != 0) && (strcasecmp(arg, "none") != 0)) {
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
+              "Ignoring deprecated use of DefaultType in line %d of %s.",
+                     cmd->directive->line_num, cmd->directive->filename);
+    }
+
+    return NULL;
+}
+
 /*
  * Note what data should be used when forming file ETag values.
  * It would be nicer to do this as an ITERATE, but then we couldn't
  * remember the +/- state properly.
  */
 static const char *set_etag_bits(cmd_parms *cmd, void *mconfig,
