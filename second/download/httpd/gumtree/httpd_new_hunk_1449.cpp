    ap_sync_scoreboard_image();

    for (i = 0; i < HARD_SERVER_LIMIT; ++i) {

	score_record = ap_scoreboard_image->servers[i];

	ps_record = ap_scoreboard_image->parent[i];

	res = score_record.status;

	stat_buffer[i] = status_flags[res];

	pid_buffer[i] = (int) ps_record.pid;

	if (res == SERVER_READY)

	    ready++;

	else if (res != SERVER_DEAD)

	    busy++;

	if (ap_extended_status) {

	    lres = score_record.access_count;

	    bytes = score_record.bytes_served;

	    if (lres != 0 || (res != SERVER_READY && res != SERVER_DEAD)) {

#ifndef NO_TIMES

		tu += score_record.times.tms_utime;

		ts += score_record.times.tms_stime;

		tcu += score_record.times.tms_cutime;

		tcs += score_record.times.tms_cstime;

#endif /* NO_TIMES */

		count += lres;

		bcount += bytes;

		if (bcount >= KBYTE) {

		    kbcount += (bcount >> 10);

		    bcount = bcount & 0x3ff;

		}

	    }

	}

    }



    up_time = nowtime - ap_restart_time;



    ap_hard_timeout("send status info", r);



    if (!short_report) {

	ap_rputs("<HTML><HEAD>\n<TITLE>Apache Status</TITLE>\n</HEAD><BODY>\n", r);

	ap_rputs("<H1>Apache Server Status for ", r);

	ap_rvputs(r, ap_get_server_name(r), "</H1>\n\n", NULL);

	ap_rvputs(r, "Server Version: ",

	  ap_get_server_version(), "<br>\n", NULL);

	ap_rvputs(r, "Server Built: ",

	  ap_get_server_built(), "<br>\n<hr>\n", NULL);

	ap_rvputs(r, "Current Time: ",

	  ap_ht_time(r->pool, nowtime, DEFAULT_TIME_FORMAT, 0), "<br>\n", NULL);

	ap_rvputs(r, "Restart Time: ",

	  ap_ht_time(r->pool, ap_restart_time, DEFAULT_TIME_FORMAT, 0), 

	  "<br>\n", NULL);

	ap_rputs("Server uptime: ", r);

	show_time(r, up_time);

	ap_rputs("<br>\n", r);

    }



    if (ap_extended_status) {

	if (short_report) {

	    ap_rprintf(r, "Total Accesses: %lu\nTotal kBytes: %lu\n",

		count, kbcount);



#ifndef NO_TIMES

	    /* Allow for OS/2 not having CPU stats */

	    if (ts || tu || tcu || tcs)

		ap_rprintf(r, "CPULoad: %g\n",

		    (tu + ts + tcu + tcs) / tick / up_time * 100.);

#endif



	    ap_rprintf(r, "Uptime: %ld\n", (long) (up_time));

	    if (up_time > 0)

		ap_rprintf(r, "ReqPerSec: %g\n",

		    (float) count / (float) up_time);



	    if (up_time > 0)

		ap_rprintf(r, "BytesPerSec: %g\n",

		    KBYTE * (float) kbcount / (float) up_time);



	    if (count > 0)

		ap_rprintf(r, "BytesPerReq: %g\n",

		    KBYTE * (float) kbcount / (float) count);

	}

	else {			/* !short_report */

	    ap_rprintf(r, "Total accesses: %lu - Total Traffic: ", count);

	    format_kbyte_out(r, kbcount);



#ifndef NO_TIMES

	    /* Allow for OS/2 not having CPU stats */

	    ap_rputs("<br>\n", r);

	    ap_rprintf(r, "CPU Usage: u%g s%g cu%g cs%g",

		    tu / tick, ts / tick, tcu / tick, tcs / tick);



	    if (ts || tu || tcu || tcs)

		ap_rprintf(r, " - %.3g%% CPU load",

		    (tu + ts + tcu + tcs) / tick / up_time * 100.);

#endif



	    ap_rputs("<br>\n", r);



	    if (up_time > 0)

		ap_rprintf(r, "%.3g requests/sec - ",

			(float) count / (float) up_time);



	    if (up_time > 0) {

		format_byte_out(r, KBYTE * (float) kbcount / (float) up_time);

		ap_rputs("/second - ", r);

	    }



	    if (count > 0) {

		format_byte_out(r, KBYTE * (float) kbcount / (float) count);

		ap_rputs("/request", r);

	    }



	    ap_rputs("<br>\n", r);

	}				/* short_report */

    }					/* ap_extended_status */



    if (!short_report)

	ap_rprintf(r, "\n%d requests currently being processed, %d idle servers\n"

		,busy, ready);

    else

	ap_rprintf(r, "BusyServers: %d\nIdleServers: %d\n", busy, ready);

