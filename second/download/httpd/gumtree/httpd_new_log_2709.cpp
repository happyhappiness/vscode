ap_rvputs(r, DOCTYPE_HTML_3_2, "<html><head>\n<title>Menu for ", 
              ap_escape_html(r->pool, r->uri),
              "</title>\n</head><body>\n", NULL);