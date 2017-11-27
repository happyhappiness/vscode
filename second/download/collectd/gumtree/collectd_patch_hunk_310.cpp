 lv_read (void)
 {
     time_t t;
     int i;
 
     if (conn == NULL) {
-        ERROR ("libvirt plugin: Not connected. Use Connection in "
-                "config file to supply connection URI.  For more information "
-                "see <http://libvirt.org/uri.html>");
-        return -1;
+        /* `conn_string == NULL' is acceptable. */
+        conn = virConnectOpenReadOnly (conn_string);
+        if (conn == NULL) {
+            c_complain (LOG_ERR, &conn_complain,
+                    "libvirt plugin: Unable to connect: "
+                    "virConnectOpenReadOnly failed.");
+            return -1;
+        }
     }
+    c_release (LOG_NOTICE, &conn_complain,
+            "libvirt plugin: Connection established.");
 
     time (&t);
 
     /* Need to refresh domain or device lists? */
     if ((last_refresh == (time_t) 0) ||
             ((interval > 0) && ((last_refresh + interval) <= t))) {
-        if (refresh_lists () != 0)
+        if (refresh_lists () != 0) {
+            if (conn != NULL)
+                virConnectClose (conn);
+            conn = NULL;
             return -1;
+        }
         last_refresh = t;
     }
 
 #if 0
     for (i = 0; i < nr_domains; ++i)
         fprintf (stderr, "domain %s\n", virDomainGetName (domains[i]));
