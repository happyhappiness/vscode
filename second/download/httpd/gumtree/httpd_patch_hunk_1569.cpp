         apr_table_setn(hdrs, "Accept-Encoding", r_accept_enc);
     }
 
     if (emit_amble) {
         emit_preamble(r, emit_xhtml, title);
     }
+    
+    d = (autoindex_config_rec *) ap_get_module_config(r->per_dir_config, &autoindex_module);
+    
     if (emit_H1) {
+        if (d->style_sheet != NULL) {
+    	    /* Insert style id if stylesheet used */
+    	    ap_rvputs(r, "  <h1 id=\"indextitle\">Index of ", title, "</h1>\n", NULL);
+    	} else {
         ap_rvputs(r, "<h1>Index of ", title, "</h1>\n", NULL);
     }
+    }
     if (rr != NULL) {
         ap_destroy_sub_req(rr);
     }
 }
 
 
