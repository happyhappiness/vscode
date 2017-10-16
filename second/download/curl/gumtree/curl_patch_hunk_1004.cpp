 #include "tool_cfgable.h"
 #include "tool_msgs.h"
 
 #include "memdebug.h" /* keep this as LAST include */
 
 #define WARN_PREFIX "Warning: "
-#define WARN_TEXTWIDTH (79 - (int)strlen(WARN_PREFIX))
+#define NOTE_PREFIX "Note: "
 
-/*
- * Emit warning formatted message on configured 'errors' stream unless
- * mute (--silent) was selected.
- */
-
-void warnf(struct GlobalConfig *config, const char *fmt, ...)
+static void voutf(struct GlobalConfig *config,
+                  const char *prefix,
+                  const char *fmt,
+                  va_list ap)
 {
+  size_t width = (79 - (int)strlen(prefix));
   if(!config->mute) {
-    va_list ap;
-    int len;
+    size_t len;
     char *ptr;
     char print_buffer[256];
 
-    va_start(ap, fmt);
     len = vsnprintf(print_buffer, sizeof(print_buffer), fmt, ap);
-    va_end(ap);
 
     ptr = print_buffer;
     while(len > 0) {
-      fputs(WARN_PREFIX, config->errors);
+      fputs(prefix, config->errors);
 
-      if(len > (int)WARN_TEXTWIDTH) {
-        int cut = WARN_TEXTWIDTH-1;
+      if(len > width) {
+        size_t cut = width-1;
 
         while(!ISSPACE(ptr[cut]) && cut) {
           cut--;
         }
         if(0 == cut)
           /* not a single cutting position was found, just cut it at the
              max text width then! */
-          cut = WARN_TEXTWIDTH-1;
+          cut = width-1;
 
         (void)fwrite(ptr, cut + 1, 1, config->errors);
         fputs("\n", config->errors);
         ptr += cut+1; /* skip the space too */
         len -= cut;
       }
