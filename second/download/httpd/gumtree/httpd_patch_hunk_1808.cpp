             good++;
             close_connection(c);
             return;
         }
         /* catch legitimate fatal apr_socket_recv errors */
         else if (status != APR_SUCCESS) {
-            err_except++; /* XXX: is this the right error counter? */
-            /* XXX: Should errors here be fatal, or should we allow a
-             * certain number of them before completely failing? -aaron */
-            apr_err("apr_socket_recv", status);
+            err_recv++;
+            if (recverrok) {
+                bad++;
+                close_connection(c);
+                if (verbosity >= 1) {
+                    char buf[120];
+                    fprintf(stderr,"%s: %s (%d)\n", "apr_socket_recv", apr_strerror(status, buf, sizeof buf), status);
+                }
+                return;
+            } else {
+                apr_err("apr_socket_recv", status);
+            }
         }
     }
 
     totalread += r;
     if (c->read == 0) {
         c->beginread = apr_time_now();
