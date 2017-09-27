                                (long)req_time);
 
                     ap_rprintf(r, "</td><td>%-1.1f</td><td>%-2.2f</td><td>%-2.2f\n",
                                (float)conn_bytes / KBYTE, (float) my_bytes / MBYTE,
                                (float)bytes / MBYTE);
 
-                    if (ws_record->status == SERVER_BUSY_READ)
-                        ap_rprintf(r,
-                                   "</td><td>?</td><td nowrap>?</td><td nowrap>..reading.. </td></tr>\n\n");
-                    else
-                        ap_rprintf(r,
-                                   "</td><td>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n\n",
-                                   ap_escape_html(r->pool,
-                                                  ws_record->client),
-                                   ap_escape_html(r->pool,
-                                                  ws_record->vhost),
-                                   ap_escape_html(r->pool,
-                                                  ap_escape_logitem(r->pool, 
-                                                                    ws_record->request)));
+                    ap_rprintf(r, "</td><td>%s</td><td nowrap>%s</td>"
+                                  "<td nowrap>%s</td></tr>\n\n",
+                               ap_escape_html(r->pool,
+                                              ws_record->client),
+                               ap_escape_html(r->pool,
+                                              ws_record->vhost),
+                               ap_escape_html(r->pool,
+                                              ap_escape_logitem(r->pool, 
+                                                      ws_record->request)));
                 } /* no_table_report */
             } /* for (j...) */
         } /* for (i...) */
 
         if (!no_table_report) {
             ap_rputs("</table>\n \
