             }
             else if (tok[0] == '*') {
                 /* we may use any variant selection algorithm, configure
                  * to use the Apache algorithm
                  */
                 neg->may_choose = 1;
-                
+
                 /* We disable header fiddles on the assumption that a
                  * client sending Negotiate knows how to send correct
                  * headers which don't need fiddling.
                  */
-                neg->dont_fiddle_headers = 1; 
+                neg->dont_fiddle_headers = 1;
             }
         }
     }
 
 #ifdef NEG_DEBUG
-    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
+    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
             "dont_fiddle_headers=%d use_rvsa=%d ua_supports_trans=%d "
             "send_alternates=%d, may_choose=%d",
-            neg->dont_fiddle_headers, neg->use_rvsa,  
+            neg->dont_fiddle_headers, neg->use_rvsa,
             neg->ua_supports_trans, neg->send_alternates, neg->may_choose);
 #endif
 
 }
 
 /* Sometimes clients will give us no Accept info at all; this routine sets
  * up the standard default for that case, and also arranges for us to be
  * willing to run a CGI script if we find one.  (In fact, we set up to
  * dramatically prefer CGI scripts in cases where that's appropriate,
  * e.g., POST or when URI includes query args or extra path info).
  */
-static void maybe_add_default_accepts(negotiation_state *neg, 
+static void maybe_add_default_accepts(negotiation_state *neg,
                                       int prefer_scripts)
 {
     accept_rec *new_accept;
 
     if (!neg->accepts) {
         neg->accepts = apr_array_make(neg->pool, 4, sizeof(accept_rec));
 
         new_accept = (accept_rec *) apr_array_push(neg->accepts);
-        
+
         new_accept->name = "*/*";
         new_accept->quality = 1.0f;
         new_accept->level = 0.0f;
-    }    
+    }
 
     new_accept = (accept_rec *) apr_array_push(neg->accepts);
 
     new_accept->name = CGI_MAGIC_TYPE;
     if (neg->use_rvsa) {
         new_accept->quality = 0;
