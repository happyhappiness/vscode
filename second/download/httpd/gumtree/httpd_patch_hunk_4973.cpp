 #ifdef HAVE_TIMES
                                ws_record->times.tms_utime / tick,
                                ws_record->times.tms_stime / tick,
                                ws_record->times.tms_cutime / tick,
                                ws_record->times.tms_cstime / tick,
 #endif
-                               last_used,
+                               (long)apr_time_sec(nowtime -
+                                                  ws_record->last_used),
                                (long) req_time);
 
                     format_byte_out(r, conn_bytes);
                     ap_rputs("|", r);
                     format_byte_out(r, my_bytes);
                     ap_rputs("|", r);
