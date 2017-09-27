            ap_rvputs(r, "value=\"", ap_escape_uri(r->pool, wsel->name), "\">\n", NULL);
            ap_rvputs(r, "<input type=hidden name=\"b\" ", NULL);
            ap_rvputs(r, "value=\"", bsel->name + sizeof("balancer://") - 1,
                      "\">\n</form>\n", NULL);
            ap_rputs("<hr />\n", r);
        }
        else if (bsel) {
            ap_rputs("<h3>Edit balancer settings for ", r);
            ap_rvputs(r, bsel->name, "</h3>\n", NULL);
            ap_rvputs(r, "<form method=\"GET\" action=\"", NULL);
            ap_rvputs(r, r->uri, "\">\n<dl>", NULL);
            ap_rputs("<table><tr><td>StickySession Identifier:</td><td><input name=\"ss\" type=text ", r);
            if (bsel->sticky)
                ap_rvputs(r, "value=\"", bsel->sticky, "\"", NULL);
            ap_rputs("></td><tr>\n<tr><td>Timeout:</td><td><input name=\"tm\" type=text ", r);
            ap_rprintf(r, "value=\"%" APR_TIME_T_FMT "\"></td></tr>\n",
                       apr_time_sec(bsel->timeout));
            ap_rputs("<tr><td>Failover Attempts:</td><td><input name=\"fa\" type=text ", r);
            ap_rprintf(r, "value=\"%d\"></td></tr>\n",
                       bsel->max_attempts);
            ap_rputs("<tr><td>LB Method:</td><td><select name=\"lm\">", r);
            {
                apr_array_header_t *methods;
                ap_list_provider_names_t *method;
                int i;
                methods = ap_list_provider_names(r->pool, PROXY_LBMETHOD, "0");
                method = (ap_list_provider_names_t *)methods->elts;
                for (i = 0; i < methods->nelts; i++) {
                    ap_rprintf(r, "<option value=\"%s\" %s>%s</option>", method->provider_name,
                       (!strcasecmp(bsel->lbmethod->name, method->provider_name)) ? "selected" : "",
                       method->provider_name);
                    method++;
                }
            }
            ap_rputs("</select></td></tr>\n", r);
            ap_rputs("<tr><td colspan=2><input type=submit value=\"Submit\"></td></tr>\n", r);
            ap_rvputs(r, "</table>\n<input type=hidden name=\"b\" ", NULL);
            ap_rvputs(r, "value=\"", bsel->name + sizeof("balancer://") - 1,
                      "\">\n</form>\n", NULL);
            ap_rputs("<hr />\n", r);
        }
        ap_rputs(ap_psignature("",r), r);
        ap_rputs("</body></html>\n", r);
    }
    return OK;
}

