             break;
 
         ++itr;
     }
 
     if (*state == HDR_STATE_DONE_WITH_HEADERS) {
-        int status = ap_scan_script_header_err_brigade(r, ob, NULL);
-        if (status != OK) {
-            apr_bucket *b;
-
-            r->status = status;
-
-            apr_brigade_cleanup(ob);
-
-            b = apr_bucket_eos_create(c->bucket_alloc);
-
-            APR_BRIGADE_INSERT_TAIL(ob, b);
-
-            ap_pass_brigade(r->output_filters, ob);
-
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-                         "proxy: FCGI: Error parsing script headers");
-
-            return -1;
-        }
-        else {
-            return 1;
-        }
+        return 1;
     }
 
     return 0;
 }
 
 static void dump_header_to_log(request_rec *r, unsigned char fheader[],
