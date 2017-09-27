         real = proxy_interpolate(r, ent->real);
     }
     else {
         fake = ent->fake;
         real = ent->real;
     }
+
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, APLOGNO(03461)
+                  "attempting to match URI path '%s' against %s '%s' for "
+                  "proxying", r->uri, (ent->regex ? "pattern" : "prefix"),
+                  fake);
+
     if (ent->regex) {
         if (!ap_regexec(ent->regex, r->uri, AP_MAX_REG_MATCH, regm, 0)) {
             if ((real[0] == '!') && (real[1] == '\0')) {
+                ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(03462)
+                              "proxying is explicitly disabled for URI path "
+                              "'%s'; declining", r->uri);
                 return DECLINED;
             }
             /* test that we haven't reduced the URI */
             if (nocanon && ap_regexec(ent->regex, r->unparsed_uri,
                     AP_MAX_REG_MATCH, reg1, 0)) {
                 mismatch = 1;
