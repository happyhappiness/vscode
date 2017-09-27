 
     /*
      * Remember the connection information for
      * later access inside callback functions
      */
 
-    ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
+    ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(01964)
                   "Connection to child %ld established "
                   "(server %s)", c->id, sc->vhost_id);
 
     return ssl_init_ssl_connection(c, NULL);
 }
 
