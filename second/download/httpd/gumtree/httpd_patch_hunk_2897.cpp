             ++errs;
     }
 
     (void) apr_file_close(f);
 
 #if MIME_MAGIC_DEBUG
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01516)
                 MODNAME ": apprentice conf=%x file=%s m=%s m->next=%s last=%s",
                 conf,
                 conf->magicfile ? conf->magicfile : "NULL",
                 conf->magic ? "set" : "NULL",
                 (conf->magic && conf->magic->next) ? "set" : "NULL",
                 conf->last ? "set" : "NULL");
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01517)
                 MODNAME ": apprentice read %d lines, %d rules, %d errors",
                 lineno, rule, errs);
 #endif
 
 #if MIME_MAGIC_DEBUG
     prevm = 0;
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01518)
                 MODNAME ": apprentice test");
     for (m = conf->magic; m; m = m->next) {
         if (apr_isprint((((unsigned long) m) >> 24) & 255) &&
             apr_isprint((((unsigned long) m) >> 16) & 255) &&
             apr_isprint((((unsigned long) m) >> 8) & 255) &&
             apr_isprint(((unsigned long) m) & 255)) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01519)
                         MODNAME ": apprentice: POINTER CLOBBERED! "
                         "m=\"%c%c%c%c\" line=%d",
                         (((unsigned long) m) >> 24) & 255,
                         (((unsigned long) m) >> 16) & 255,
                         (((unsigned long) m) >> 8) & 255,
                         ((unsigned long) m) & 255,
