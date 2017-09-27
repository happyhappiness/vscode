     }
     else if (strncmp(l, "ledate", NLEDATE) == 0) {
         m->type = LEDATE;
         l += NLEDATE;
     }
     else {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, serv,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, serv, APLOGNO(01524)
                     MODNAME ": type %s invalid", l);
         return -1;
     }
     /* New-style anding: "0 byte&0x80 =0x80 dynamically linked" */
     if (*l == '&') {
         ++l;
