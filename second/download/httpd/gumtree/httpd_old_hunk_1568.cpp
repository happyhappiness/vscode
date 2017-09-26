        ap_rputs(DOCTYPE_HTML_3_2
                 "<html><head>\n<title>Apache Status</title>\n</head><body>\n",
                 r);
        ap_rputs("<h1>Apache Server Status for ", r);
        ap_rvputs(r, ap_get_server_name(r), "</h1>\n\n", NULL);
        ap_rvputs(r, "<dl><dt>Server Version: ",
                  ap_get_server_version(), "</dt>\n", NULL);
        ap_rvputs(r, "<dt>Server Built: ",
                  ap_get_server_built(), "\n</dt></dl><hr /><dl>\n", NULL);
        ap_rvputs(r, "<dt>Current Time: ",
                  ap_ht_time(r->pool, nowtime, DEFAULT_TIME_FORMAT, 0),
                             "</dt>\n", NULL);
        ap_rvputs(r, "<dt>Restart Time: ",
