 {
     register unsigned long l = m->value.l;
     register unsigned long v;
     int matched;
 
     if ((m->value.s[0] == 'x') && (m->value.s[1] == '\0')) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01539)
                     MODNAME ": BOINK");
         return 1;
     }
 
     switch (m->type) {
     case BYTE:
