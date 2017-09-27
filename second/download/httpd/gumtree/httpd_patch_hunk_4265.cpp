         case H2_SESSION_EV_MPM_STOPPING:
             h2_session_ev_mpm_stopping(session, arg, msg);
             break;
         case H2_SESSION_EV_PRE_CLOSE:
             h2_session_ev_pre_close(session, arg, msg);
             break;
+        case H2_SESSION_EV_STREAM_OPEN:
+            h2_session_ev_stream_open(session, arg, msg);
+            break;
+        case H2_SESSION_EV_STREAM_DONE:
+            h2_session_ev_stream_done(session, arg, msg);
+            break;
         default:
             ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                           "h2_session(%ld): unknown event %d", 
                           session->id, ev);
             break;
     }
