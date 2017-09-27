                ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td><td>", worker->s->elected);
                ap_rputs(apr_strfsize(worker->s->transferred, fbuf), r);
                ap_rputs("</td><td>", r);
                ap_rputs(apr_strfsize(worker->s->read, fbuf), r);
                ap_rputs("</td></tr>\n", r);

                ++worker;
            }
            ap_rputs("</table>\n", r);
            ++balancer;
        }
        ap_rputs("<hr />\n", r);
        if (wsel && bsel) {
            ap_rputs("<h3>Edit worker settings for ", r);
            ap_rvputs(r, wsel->name, "</h3>\n", NULL);
            ap_rvputs(r, "<form method=\"GET\" action=\"", NULL);
            ap_rvputs(r, ap_escape_uri(r->pool, r->uri), "\">\n<dl>", NULL);
            ap_rputs("<table><tr><td>Load factor:</td><td><input name=\"lf\" type=text ", r);
            ap_rprintf(r, "value=\"%d\"></td></tr>\n", wsel->s->lbfactor);
            ap_rputs("<tr><td>LB Set:</td><td><input name=\"ls\" type=text ", r);
            ap_rprintf(r, "value=\"%d\"></td></tr>\n", wsel->s->lbset);
            ap_rputs("<tr><td>Route:</td><td><input name=\"wr\" type=text ", r);
            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->route),
