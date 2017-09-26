                    ap_rputs(")\n", r);
                    ap_rprintf(r,
                               " <i>%s {%s}</i> <b>[%s]</b><br />\n\n",
                               ap_escape_html(r->pool,
                                              ws_record->client),
                               ap_escape_html(r->pool,
                                              ap_escape_logitem(r->pool,
                                                                ws_record->request)),
                               ap_escape_html(r->pool,
                                              ws_record->vhost));
                }
                else { /* !no_table_report */
                    if (ws_record->status == SERVER_DEAD)
                        ap_rprintf(r,
                                   "<tr><td><b>%d-%d</b></td><td>-</td><td>%d/%lu/%lu",
                                   i, (int)ps_record->generation,
                                   (int)conn_lres, my_lres, lres);
                    else
                        ap_rprintf(r,
                                   "<tr><td><b>%d-%d</b></td><td>%"
                                   APR_PID_T_FMT
                                   "</td><td>%d/%lu/%lu",
                                   i, (int)ps_record->generation,
                                   ps_record->pid, (int)conn_lres,
                                   my_lres, lres);
                    
                    switch (ws_record->status) {
                    case SERVER_READY:
                        ap_rputs("</td><td>_", r);
                        break;
                    case SERVER_STARTING:
                        ap_rputs("</td><td><b>S</b>", r);
