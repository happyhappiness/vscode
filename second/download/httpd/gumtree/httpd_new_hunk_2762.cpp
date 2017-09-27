    /* up_time in seconds */
    up_time = (apr_uint32_t) apr_time_sec(nowtime -
                               ap_scoreboard_image->global->restart_time);

    if (!short_report) {
        ap_rputs(DOCTYPE_HTML_3_2
                 "<html><head>\n"
                 "<title>Apache Status</title>\n"
                 "</head><body>\n"
                 "<h1>Apache Server Status for ", r);
        ap_rvputs(r, ap_get_server_name(r), " (via ", r->connection->local_ip,
                  ")</h1>\n\n", NULL);
        ap_rvputs(r, "<dl><dt>Server Version: ",
                  ap_get_server_description(), "</dt>\n", NULL);
        ap_rvputs(r, "<dt>Server Built: ",
                  ap_get_server_built(), "\n</dt></dl><hr /><dl>\n", NULL);
        ap_rvputs(r, "<dt>Current Time: ",
                  ap_ht_time(r->pool, nowtime, DEFAULT_TIME_FORMAT, 0),
                             "</dt>\n", NULL);
        ap_rvputs(r, "<dt>Restart Time: ",
                  ap_ht_time(r->pool,
                             ap_scoreboard_image->global->restart_time,
                             DEFAULT_TIME_FORMAT, 0),
                  "</dt>\n", NULL);
        ap_rprintf(r, "<dt>Parent Server Config. Generation: %d</dt>\n",
                   ap_state_query(AP_SQ_CONFIG_GEN));
        ap_rprintf(r, "<dt>Parent Server MPM Generation: %d</dt>\n",
                   (int)mpm_generation);
        ap_rputs("<dt>Server uptime: ", r);
        show_time(r, up_time);
        ap_rputs("</dt>\n", r);
    }

