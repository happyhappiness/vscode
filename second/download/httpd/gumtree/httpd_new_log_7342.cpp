ap_rvputs(r, "          <httpd:route>",
                          ap_escape_html(r->pool, worker->s->route),
                          "</httpd:route>\n", NULL);