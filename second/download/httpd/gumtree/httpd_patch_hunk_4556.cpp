                 nghttp2_priority_spec_init(&ps, id_parent, valid_weight(prio->weight), 0);
                 break;
         }
 
 
         rv = nghttp2_session_change_stream_priority(session->ngh2, stream->id, &ps);
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03203)
-                      "h2_stream(%ld-%d): PUSH %s, weight=%d, "
-                      "depends=%d, returned=%d",
-                      session->id, stream->id, ptype, 
-                      ps.weight, ps.stream_id, rv);
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
+                      ""H2_STRM_LOG(APLOGNO(03203), stream, 
+                      "PUSH %s, weight=%d, depends=%d, returned=%d"),
+                      ptype, ps.weight, ps.stream_id, rv);
         status = (rv < 0)? APR_EGENERAL : APR_SUCCESS;
     }
 #else
     (void)session;
     (void)stream;
     (void)prio;
