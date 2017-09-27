         h2_ihash_clear(m->spurge);
     }
 }
 
 static void h2_mplx_destroy(h2_mplx *m)
 {
-    AP_DEBUG_ASSERT(m);
+    conn_rec **pslave;
+    ap_assert(m);
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                   "h2_mplx(%ld): destroy, tasks=%d", 
                   m->id, (int)h2_ihash_count(m->tasks));
     check_tx_free(m);
+    
+    while (m->spare_slaves->nelts > 0) {
+        pslave = (conn_rec **)apr_array_pop(m->spare_slaves);
+        h2_slave_destroy(*pslave);
+    }
     if (m->pool) {
         apr_pool_destroy(m->pool);
     }
 }
 
 /**
