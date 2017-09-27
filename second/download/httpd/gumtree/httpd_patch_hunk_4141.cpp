                         start_lingering_close_nonblocking(cs);
                         break;
                     }
                     rc = push2worker(out_pfd, event_pollset);
                     if (rc != APR_SUCCESS) {
                         ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
-                                     ap_server_conf, "push2worker failed");
+                                     ap_server_conf, APLOGNO(03095)
+                                     "push2worker failed");
                     }
                     else {
                         have_idle_worker = 0;
                     }
                     break;
                 case CONN_STATE_LINGER_NORMAL:
                 case CONN_STATE_LINGER_SHORT:
                     process_lingering_close(cs, out_pfd);
                     break;
                 default:
                     ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
-                                 ap_server_conf,
+                                 ap_server_conf, APLOGNO(03096)
                                  "event_loop: unexpected state %d",
                                  cs->pub.state);
                     ap_assert(0);
                 }
             }
             else if (pt->type == PT_ACCEPT) {
