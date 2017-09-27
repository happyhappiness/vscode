    if (!short_report)
        ap_rprintf(r, "<dt>%d requests currently being processed, "
                      "%d idle workers</dt>\n", busy, ready);
    else
        ap_rprintf(r, "BusyWorkers: %d\nIdleWorkers: %d\n", busy, ready);

    /* send the scoreboard 'table' out */
    if (!short_report)
        ap_rputs("</dl><pre>", r);
    else
        ap_rputs("Scoreboard: ", r);

    for (i = 0; i < server_limit; ++i) {
        for (j = 0; j < thread_limit; ++j) {
            int indx = (i * thread_limit) + j;
            ap_rputc(stat_buffer[indx], r);
            if ((indx % STATUS_MAXLINE == (STATUS_MAXLINE - 1))
                && !short_report)
                ap_rputs("\n", r);
        }
    }

    if (short_report)
        ap_rputs("\n", r);
    else {
        ap_rputs("</pre>\n", r);
        ap_rputs("<p>Scoreboard Key:<br />\n", r);
        ap_rputs("\"<b><code>_</code></b>\" Waiting for Connection, \n", r);
        ap_rputs("\"<b><code>S</code></b>\" Starting up, \n", r);
        ap_rputs("\"<b><code>R</code></b>\" Reading Request,<br />\n", r);
        ap_rputs("\"<b><code>W</code></b>\" Sending Reply, \n", r);
        ap_rputs("\"<b><code>K</code></b>\" Keepalive (read), \n", r);
        ap_rputs("\"<b><code>D</code></b>\" DNS Lookup,<br />\n", r);
        ap_rputs("\"<b><code>C</code></b>\" Closing connection, \n", r);
        ap_rputs("\"<b><code>L</code></b>\" Logging, \n", r);
        ap_rputs("\"<b><code>G</code></b>\" Gracefully finishing,<br /> \n", r);
        ap_rputs("\"<b><code>I</code></b>\" Idle cleanup of worker, \n", r);
        ap_rputs("\"<b><code>.</code></b>\" Open slot with no current process</p>\n", r);
        ap_rputs("<p />\n", r);
        if (!ap_extended_status) {
            int j;
            int k = 0;
            ap_rputs("PID Key: <br />\n", r);
            ap_rputs("<pre>\n", r);
            for (i = 0; i < server_limit; ++i) {
                for (j = 0; j < thread_limit; ++j) {
                    int indx = (i * thread_limit) + j;

                    if (stat_buffer[indx] != '.') {
                        ap_rprintf(r, "   %" APR_PID_T_FMT
