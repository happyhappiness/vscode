                                   "</td><td>%s</td><td nowrap>%s</td><td nowrap>%s</td></tr>\n\n",
                                   ap_escape_html(r->pool,
                                                  ws_record->client),
                                   ap_escape_html(r->pool,
                                                  ws_record->vhost),
                                   ap_escape_html(r->pool,
                                                  ws_record->request));
                } /* no_table_report */
            } /* for (j...) */
        } /* for (i...) */

        if (!no_table_report) {
            ap_rputs("</table>\n \
