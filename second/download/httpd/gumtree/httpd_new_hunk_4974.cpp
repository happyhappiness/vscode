#ifdef HAVE_TIMES
                               (ws_record->times.tms_utime +
                                ws_record->times.tms_stime +
                                ws_record->times.tms_cutime +
                                ws_record->times.tms_cstime) / tick,
#endif
                               (long)apr_time_sec(nowtime -
                                                  ws_record->last_used),
                               (long)req_time);

                    ap_rprintf(r, "</td><td>%-1.1f</td><td>%-2.2f</td><td>%-2.2f\n",
                               (float)conn_bytes / KBYTE, (float) my_bytes / MBYTE,
                               (float)bytes / MBYTE);

                    ap_rprintf(r, "</td><td>%s</td><td nowrap>%s</td>"
                                  "<td nowrap>%s</td></tr>\n\n",
                               ap_escape_html(r->pool,
                                              ws_record->client),
                               ap_escape_html(r->pool,
                                              ws_record->vhost),
                               ap_escape_html(r->pool,
                                              ap_escape_logitem(r->pool,
                                                      ws_record->request)));
                } /* no_table_report */
            } /* for (j...) */
        } /* for (i...) */

        if (!no_table_report) {
            ap_rputs("</table>\n \
<hr /> \
<table>\n \
<tr><th>Srv</th><td>Child Server number - generation</td></tr>\n \
<tr><th>PID</th><td>OS process ID</td></tr>\n \
<tr><th>Acc</th><td>Number of accesses this connection / this child / this slot</td></tr>\n \
