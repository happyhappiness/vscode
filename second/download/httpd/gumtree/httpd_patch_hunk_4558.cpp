         
         if (!stream->pref_priority) {
             stream->pref_priority = h2_stream_get_priority(stream, headers);
         }
         h2_session_set_prio(session, stream, stream->pref_priority);
         
-        hout = headers->headers;
         note = apr_table_get(headers->notes, H2_FILTER_DEBUG_NOTE);
         if (note && !strcmp("on", note)) {
             int32_t connFlowIn, connFlowOut;
 
             connFlowIn = nghttp2_session_get_effective_local_window_size(session->ngh2); 
             connFlowOut = nghttp2_session_get_remote_window_size(session->ngh2);
-            hout = apr_table_clone(stream->pool, hout);
-            apr_table_setn(hout, "conn-flow-in", 
+            headers = h2_headers_copy(stream->pool, headers);
+            apr_table_setn(headers->headers, "conn-flow-in", 
                            apr_itoa(stream->pool, connFlowIn));
-            apr_table_setn(hout, "conn-flow-out", 
+            apr_table_setn(headers->headers, "conn-flow-out", 
                            apr_itoa(stream->pool, connFlowOut));
         }
         
         if (headers->status == 103 
             && !h2_config_geti(session->config, H2_CONF_EARLY_HINTS)) {
             /* suppress sending this to the client, it might have triggered 
              * pushes and served its purpose nevertheless */
             rv = 0;
             goto leave;
         }
         
-        ngh = h2_util_ngheader_make_res(stream->pool, headers->status, hout);
-        rv = nghttp2_submit_response(session->ngh2, stream->id,
-                                     ngh->nv, ngh->nvlen, pprovider);
-        stream->has_response = h2_headers_are_response(headers);
-        session->have_written = 1;
-        
-        if (stream->initiated_on) {
-            ++session->pushes_submitted;
+        status = h2_res_create_ngheader(&ngh, stream->pool, headers);
+        if (status == APR_SUCCESS) {
+            rv = nghttp2_submit_response(session->ngh2, stream->id,
+                                         ngh->nv, ngh->nvlen, pprovider);
+            stream->has_response = h2_headers_are_response(headers);
+            session->have_written = 1;
+            
+            if (stream->initiated_on) {
+                ++session->pushes_submitted;
+            }
+            else {
+                ++session->responses_submitted;
+            }
         }
         else {
-            ++session->responses_submitted;
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
+                          H2_STRM_LOG(APLOGNO(10025), stream, "invalid response"));
+            h2_stream_rst(stream, NGHTTP2_PROTOCOL_ERROR);
         }
     }
     
 leave:
     if (nghttp2_is_fatal(rv)) {
         status = APR_EGENERAL;
