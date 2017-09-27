             csd_data->is_secure = 1;
         }
     }
     else {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                      "Upgradeable socket handle not found");
-        return ap_pass_brigade(f->next, bb);
+        return AP_FILTER_ERROR;
     }
 
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                  "Awaiting re-negotiation handshake");
 
-    return ap_pass_brigade(f->next, bb);
+    /* Now that we have initialized the ssl connection which added the ssl_io_filter,
+       pass the brigade off to the connection based output filters so that the
+       request can complete encrypted */
+    return ap_pass_brigade(f->c->output_filters, bb);
 }
 
 static void ssl_hook_Insert_Filter(request_rec *r)
 {
     NWSSLSrvConfigRec *sc = get_nwssl_cfg(r->server);
 
