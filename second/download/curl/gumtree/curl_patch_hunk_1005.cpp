       }
     }
   }
 }
 
 /*
+ * Emit 'note' formatted message on configured 'errors' stream, if verbose was
+ * selected.
+ */
+void notef(struct GlobalConfig *config, const char *fmt, ...)
+{
+  va_list ap;
+  va_start(ap, fmt);
+  if(config->tracetype)
+    voutf(config, NOTE_PREFIX, fmt, ap);
+  va_end(ap);
+}
+
+/*
+ * Emit warning formatted message on configured 'errors' stream unless
+ * mute (--silent) was selected.
+ */
+
+void warnf(struct GlobalConfig *config, const char *fmt, ...)
+{
+  va_list ap;
+  va_start(ap, fmt);
+  voutf(config, WARN_PREFIX, fmt, ap);
+  va_end(ap);
+}
+/*
  * Emit help formatted message on given stream.
  */
 
 void helpf(FILE *errors, const char *fmt, ...)
 {
   va_list ap;
