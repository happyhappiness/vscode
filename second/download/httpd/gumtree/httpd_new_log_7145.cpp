ap_rvputs(r, "          <httpd:redirect>",
                          ap_escape_html(r->pool, worker->s->redirect),
                          "</httpd:redirect>\n", NULL);