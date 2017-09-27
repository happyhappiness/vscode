     return APR_ENOMEM;
 }
 
 /*
  * print purge statistics
  */
-static void printstats(apr_off_t total, apr_off_t sum, apr_off_t max,
-                       apr_off_t etotal, apr_off_t entries)
+static void printstats(char *path, struct stats *s)
 {
     char ttype, stype, mtype, utype;
     apr_off_t tfrag, sfrag, ufrag;
 
     if (!verbose) {
         return;
     }
 
     ttype = 'K';
-    tfrag = ((total * 10) / KBYTE) % 10;
-    total /= KBYTE;
-    if (total >= KBYTE) {
+    tfrag = ((s->total * 10) / KBYTE) % 10;
+    s->total /= KBYTE;
+    if (s->total >= KBYTE) {
         ttype = 'M';
-        tfrag = ((total * 10) / KBYTE) % 10;
-        total /= KBYTE;
+        tfrag = ((s->total * 10) / KBYTE) % 10;
+        s->total /= KBYTE;
     }
 
     stype = 'K';
-    sfrag = ((sum * 10) / KBYTE) % 10;
-    sum /= KBYTE;
-    if (sum >= KBYTE) {
+    sfrag = ((s->sum * 10) / KBYTE) % 10;
+    s->sum /= KBYTE;
+    if (s->sum >= KBYTE) {
         stype = 'M';
-        sfrag = ((sum * 10) / KBYTE) % 10;
-        sum /= KBYTE;
+        sfrag = ((s->sum * 10) / KBYTE) % 10;
+        s->sum /= KBYTE;
     }
 
     mtype = 'K';
-    max /= KBYTE;
-    if (max >= KBYTE) {
+    s->max /= KBYTE;
+    if (s->max >= KBYTE) {
         mtype = 'M';
-        max /= KBYTE;
+        s->max /= KBYTE;
     }
 
-    apr_file_printf(errfile, "Statistics:" APR_EOL_STR);
+    apr_file_printf(errfile, "Cleaned %s. Statistics:" APR_EOL_STR, path);
     if (unsolicited) {
         utype = 'K';
         ufrag = ((unsolicited * 10) / KBYTE) % 10;
         unsolicited /= KBYTE;
         if (unsolicited >= KBYTE) {
             utype = 'M';
