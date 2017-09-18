	ap_rputs("\"<B><code>W</code></B>\" Sending Reply, \n", r);
	ap_rputs("\"<B><code>K</code></B>\" Keepalive (read), \n", r);
	ap_rputs("\"<B><code>D</code></B>\" DNS Lookup,<BR>\n", r);
	ap_rputs("\"<B><code>L</code></B>\" Logging, \n", r);
	ap_rputs("\"<B><code>G</code></B>\" Gracefully finishing, \n", r);
	ap_rputs("\"<B><code>.</code></B>\" Open slot with no current process<P>\n", r);
	ap_rputs("<P>\n", r);
	if (!ap_extended_status) {
	    int j = 0;
	    ap_rputs("PID Key: <br>\n", r);
	    ap_rputs("<PRE>\n", r);
	    for (i = 0; i < HARD_SERVER_LIMIT; ++i) {
		if (stat_buffer[i] != '.') {
		    ap_rprintf(r, "   %d in state: %c ", pid_buffer[i],
		     stat_buffer[i]);
		    if (++j >= 3) {
		    	ap_rputs("\n", r);
			j = 0;
		    } else
		    	ap_rputs(",", r);
		}
	    }
	    ap_rputs("\n", r);
	    ap_rputs("</PRE>\n", r);
	}
    }

    if (ap_extended_status) {
	if (!short_report) {
	    if (no_table_report)
		ap_rputs("<p><hr><h2>Server Details</h2>\n\n", r);
	    else
#ifdef NO_TIMES
		/* Allow for OS/2 not having CPU stats */
		ap_rputs("<p>\n\n<table border=0><tr><th>Srv<th>PID<th>Acc<th>M\n<th>SS<th>Req<th>Conn<th>Child<th>Slot<th>Client<th>VHost<th>Request</tr>\n\n", r);
#else
		ap_rputs("<p>\n\n<table border=0><tr><th>Srv<th>PID<th>Acc<th>M<th>CPU\n<th>SS<th>Req<th>Conn<th>Child<th>Slot<th>Client<th>VHost<th>Request</tr>\n\n", r);
#endif
	}

	for (i = 0; i < HARD_SERVER_LIMIT; ++i) {
	    score_record = ap_scoreboard_image->servers[i];
	    ps_record = ap_scoreboard_image->parent[i];

#if defined(NO_GETTIMEOFDAY)
#ifndef NO_TIMES
	    if (score_record.start_time == (clock_t) 0)
#endif /* NO_TIMES */
		req_time = 0L;
#ifndef NO_TIMES
	    else {
		req_time = score_record.stop_time - score_record.start_time;
		req_time = (req_time * 1000) / (int) tick;
	    }
#endif /* NO_TIMES */
#else
	    if (score_record.start_time.tv_sec == 0L &&
		score_record.start_time.tv_usec == 0L)
		req_time = 0L;
	    else
		req_time =
		    ((score_record.stop_time.tv_sec - score_record.start_time.tv_sec) * 1000) +
		    ((score_record.stop_time.tv_usec - score_record.start_time.tv_usec) / 1000);
#endif
	    if (req_time < 0L)
		req_time = 0L;

	    lres = score_record.access_count;
	    my_lres = score_record.my_access_count;
	    conn_lres = score_record.conn_count;
	    bytes = score_record.bytes_served;
	    my_bytes = score_record.my_bytes_served;
	    conn_bytes = score_record.conn_bytes;
	    if (lres != 0 || (score_record.status != SERVER_READY
			      && score_record.status != SERVER_DEAD)) {
		if (!short_report) {
		    if (no_table_report) {
			if (score_record.status == SERVER_DEAD)
			    ap_rprintf(r, "<b>Server %d</b> (-): %d|%lu|%lu [",
				    i, (int) conn_lres, my_lres, lres);
			else
			    ap_rprintf(r, "<b>Server %d</b> (%d): %d|%lu|%lu [",
				    i, (int) ps_record.pid, (int) conn_lres, my_lres, lres);

			switch (score_record.status) {
			case SERVER_READY:
			    ap_rputs("Ready", r);
			    break;
			case SERVER_STARTING:
			    ap_rputs("Starting", r);
			    break;
			case SERVER_BUSY_READ:
			    ap_rputs("<b>Read</b>", r);
			    break;
			case SERVER_BUSY_WRITE:
			    ap_rputs("<b>Write</b>", r);
			    break;
			case SERVER_BUSY_KEEPALIVE:
			    ap_rputs("<b>Keepalive</b>", r);
			    break;
			case SERVER_BUSY_LOG:
			    ap_rputs("<b>Logging</b>", r);
			    break;
			case SERVER_BUSY_DNS:
			    ap_rputs("<b>DNS lookup</b>", r);
			    break;
			case SERVER_DEAD:
			    ap_rputs("Dead", r);
			    break;
			case SERVER_GRACEFUL:
			    ap_rputs("Graceful", r);
			    break;
			default:
			    ap_rputs("?STATE?", r);
			    break;
			}
#ifdef NO_TIMES
			/* Allow for OS/2 not having CPU stats */
			ap_rprintf(r, "]\n %.0f %ld (",
#else

			ap_rprintf(r, "] u%g s%g cu%g cs%g\n %.0f %ld (",
			    score_record.times.tms_utime / tick,
			    score_record.times.tms_stime / tick,
			    score_record.times.tms_cutime / tick,
			    score_record.times.tms_cstime / tick,
#endif
#ifdef OPTIMIZE_TIMEOUTS
			    difftime(nowtime, ps_record.last_rtime),
#else
			    difftime(nowtime, score_record.last_used),
#endif
			    (long) req_time);
			format_byte_out(r, conn_bytes);
			ap_rputs("|", r);
			format_byte_out(r, my_bytes);
			ap_rputs("|", r);
			format_byte_out(r, bytes);
			ap_rputs(")\n", r);
			ap_rprintf(r, " <i>%s {%s}</i><br>\n\n",
				score_record.client,
				ap_escape_html(r->pool, score_record.request));
		    }
		    else {		/* !no_table_report */
			if (score_record.status == SERVER_DEAD)
			    ap_rprintf(r, "<tr><td><b>%d</b><td>-<td>%d/%lu/%lu",
				    i, (int) conn_lres, my_lres, lres);
			else
			    ap_rprintf(r, "<tr><td><b>%d</b><td>%d<td>%d/%lu/%lu",
				    i, (int) ps_record.pid, (int) conn_lres, my_lres, lres);

			switch (score_record.status) {
			case SERVER_READY:
			    ap_rputs("<td>_", r);
			    break;
			case SERVER_STARTING:
			    ap_rputs("<td><b>S</b>", r);
			    break;
			case SERVER_BUSY_READ:
			    ap_rputs("<td><b>R</b>", r);
			    break;
			case SERVER_BUSY_WRITE:
			    ap_rputs("<td><b>W</b>", r);
			    break;
			case SERVER_BUSY_KEEPALIVE:
			    ap_rputs("<td><b>K</b>", r);
			    break;
			case SERVER_BUSY_LOG:
			    ap_rputs("<td><b>L</b>", r);
			    break;
			case SERVER_BUSY_DNS:
			    ap_rputs("<td><b>D</b>", r);
			    break;
			case SERVER_DEAD:
			    ap_rputs("<td>.", r);
			    break;
			case SERVER_GRACEFUL:
			    ap_rputs("<td>G", r);
			    break;
			default:
			    ap_rputs("<td>?", r);
			    break;
			}
#ifdef NO_TIMES
			/* Allow for OS/2 not having CPU stats */
			ap_rprintf(r, "\n<td>%.0f<td>%ld",
#else
			ap_rprintf(r, "\n<td>%.2f<td>%.0f<td>%ld",
			    (score_record.times.tms_utime +
			     score_record.times.tms_stime +
			     score_record.times.tms_cutime +
			     score_record.times.tms_cstime) / tick,
#endif
#ifdef OPTIMIZE_TIMEOUTS
			    difftime(nowtime, ps_record.last_rtime),
#else
			    difftime(nowtime, score_record.last_used),
#endif
			    (long) req_time);
			ap_rprintf(r, "<td>%-1.1f<td>%-2.2f<td>%-2.2f\n",
			   (float) conn_bytes / KBYTE, (float) my_bytes / MBYTE,
			    (float) bytes / MBYTE);
			if (score_record.status == SERVER_BUSY_READ)
			    ap_rprintf(r,
			     "<td>?<td nowrap>?<td nowrap>..reading.. </tr>\n\n");
			else
			    ap_rprintf(r,
			     "<td>%s<td nowrap>%s<td nowrap>%s</tr>\n\n",
			     score_record.client, score_record.vhost,
			     ap_escape_html(r->pool, score_record.request));
		    }		/* no_table_report */
		}			/* !short_report */
	    }			/* if (<active child>) */
	}				/* for () */

	if (!(short_report || no_table_report)) {
#ifdef NO_TIMES
	    ap_rputs("</table>\n \
<hr> \
<table>\n \
<tr><th>Srv<td>Server number\n \
<tr><th>PID<td>OS process ID\n \
<tr><th>Acc<td>Number of accesses this connection / this child / this slot\n \
<tr><th>M<td>Mode of operation\n \
