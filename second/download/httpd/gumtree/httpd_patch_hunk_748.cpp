 
             /* Pass our apr_table_t to http_protocol.c (see mod_negotiation): */
             apr_table_setn(notes, "variant-list", apr_array_pstrcat(p, t, 0));
 
 	    apr_table_mergen(r->subprocess_env, "VARIANTS",
 			    apr_array_pstrcat(p, v, ','));
-	  
+
 	    apr_pool_destroy(sub_pool);
 
             ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
 			 ref ? "Spelling fix: %s: %d candidates from %s"
 			     : "Spelling fix: %s: %d candidates",
 			 r->uri, candidates->nelts, ref);
