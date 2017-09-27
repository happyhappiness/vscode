             /* no showstopper if that fails for some reason */
         }
         
         ngh = h2_util_ngheader_make_res(stream->pool, response->http_status, 
                                         response->headers);
         rv = nghttp2_submit_response(session->ngh2, response->stream_id,
-                                     ngh->nv, ngh->nvlen, &provider);
-        
+                                     ngh->nv, ngh->nvlen, pprovider);
     }
     else {
         int err = H2_STREAM_RST(stream, H2_ERR_PROTOCOL_ERROR);
         
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03074)
                       "h2_stream(%ld-%d): RST_STREAM, err=%d",
                       session->id, stream->id, err);
 
         rv = nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
                                        stream->id, err);
     }
     
     stream->submitted = 1;
+    if (stream->request && stream->request->initiated_on) {
+        ++session->pushes_submitted;
+    }
+    else {
+        ++session->responses_submitted;
+    }
 
     if (nghttp2_is_fatal(rv)) {
         status = APR_EGENERAL;
-        h2_session_abort_int(session, rv);
+        dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, rv, nghttp2_strerror(rv));
         ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                       APLOGNO(02940) "submit_response: %s", 
                       nghttp2_strerror(rv));
     }
     
     return status;
