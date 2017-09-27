
    /* up_time in seconds */
    up_time = (apr_uint32_t) apr_time_sec(nowtime -
                               ap_scoreboard_image->global->restart_time);

    if (!short_report) {
        ap_loadavg_t t;

        ap_rputs(DOCTYPE_HTML_3_2
                 "<html><head>\n"
                 "<title>Apache Status</title>\n"
                 "</head><body>\n"
                 "<h1>Apache Server Status for ", r);
        ap_rvputs(r, ap_escape_html(r->pool, ap_get_server_name(r)),
                  " (via ", r->connection->local_ip,
                  ")</h1>\n\n", NULL);
        ap_rvputs(r, "<dl><dt>Server Version: ",
                  ap_get_server_description(), "</dt>\n", NULL);
        ap_rvputs(r, "<dt>Server Built: ",
                  ap_get_server_built(), "\n</dt></dl><hr /><dl>\n", NULL);
        ap_rvputs(r, "<dt>Current Time: ",
