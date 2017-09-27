             ap_rvputs(r, "value='", ap_escape_uri(r->pool, wsel->s->name), "'>\n", NULL);
             ap_rvputs(r, "<input type=hidden name='b' id='b' ", NULL);
             ap_rvputs(r, "value='", bsel->s->name + sizeof(BALANCER_PREFIX) - 1,
                       "'>\n", NULL);
             ap_rvputs(r, "<input type=hidden name='nonce' id='nonce' value='",
                       bsel->s->nonce, "'>\n", NULL);
-            ap_rvputs(r, "</form>\n", NULL);
+            ap_rputs("</form>\n", r);
             ap_rputs("<hr />\n", r);
         } else if (bsel) {
             const apr_array_header_t *provs;
             const ap_list_provider_names_t *pname;
             int i;
             ap_rputs("<h3>Edit balancer settings for ", r);
