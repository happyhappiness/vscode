          * while (m && m->next && m->next->cont_level != 0 && ( m = m->next
          * ))
          */
         m = m->next;
         while (m && (m->cont_level != 0)) {
 #if MIME_MAGIC_DEBUG
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01534)
                         MODNAME ": match line=%d cont=%d type=%d %s",
                         m->lineno, m->cont_level, m->type,
                         (m->type == STRING) ? m->value.s : "");
 #endif
             if (cont_level >= m->cont_level) {
                 if (cont_level > m->cont_level) {
