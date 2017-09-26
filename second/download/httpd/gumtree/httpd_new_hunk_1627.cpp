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
