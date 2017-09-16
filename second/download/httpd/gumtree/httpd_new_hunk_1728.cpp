	r->status_line = ap_pstrdup(p, &buffer[9]);



/* read the headers. */

/* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers */

/* Also, take care with headers with multiple occurences. */



	resp_hdrs = ap_proxy_read_headers(r, buffer, HUGE_STRING_LEN, f);

	if (resp_hdrs == NULL) {

	    ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, r->server,

		 "proxy: Bad HTTP/%d.%d header returned by %s (%s)",

		 major, minor, r->uri, r->method);

	    resp_hdrs = ap_make_table(p, 20);

	    nocache = 1;    /* do not cache this broken file */

	}



	if (conf->viaopt != via_off && conf->viaopt != via_block) {

	    /* Create a "Via:" response header entry and merge it */

	    i = ap_get_server_port(r);

	    if (ap_is_default_port(i,r)) {

		strcpy(portstr,"");

	    } else {

		ap_snprintf(portstr, sizeof portstr, ":%d", i);

	    }

	    ap_table_mergen((table *)resp_hdrs, "Via",

			    (conf->viaopt == via_full)

			    ? ap_psprintf(p, "%d.%d %s%s (%s)",

				major, minor,

				ap_get_server_name(r), portstr,

				SERVER_BASEVERSION)

			    : ap_psprintf(p, "%d.%d %s%s",

				major, minor,

				ap_get_server_name(r), portstr)

			    );

	}



	clear_connection(p, resp_hdrs);	/* Strip Connection hdrs */

    }

    else {

/* an http/0.9 response */

	backasswards = 1;

	r->status = 200;

	r->status_line = "200 OK";



/* no headers */

	resp_hdrs = ap_make_table(p, 20);

    }



    c->hdrs = resp_hdrs;



    ap_kill_timeout(r);



/*

 * HTTP/1.0 requires us to accept 3 types of dates, but only generate

 * one type

 */

    if ((datestr = ap_table_get(resp_hdrs, "Date")) != NULL)

	ap_table_set(resp_hdrs, "Date", ap_proxy_date_canon(p, datestr));

    if ((datestr = ap_table_get(resp_hdrs, "Last-Modified")) != NULL)

	ap_table_set(resp_hdrs, "Last-Modified", ap_proxy_date_canon(p, datestr));

    if ((datestr = ap_table_get(resp_hdrs, "Expires")) != NULL)

	ap_table_set(resp_hdrs, "Expires", ap_proxy_date_canon(p, datestr));



    if ((datestr = ap_table_get(resp_hdrs, "Location")) != NULL)

	ap_table_set(resp_hdrs, "Location", proxy_location_reverse_map(r, datestr));

    if ((datestr = ap_table_get(resp_hdrs, "URI")) != NULL)

	ap_table_set(resp_hdrs, "URI", proxy_location_reverse_map(r, datestr));



/* check if NoCache directive on this host */

    for (i = 0; i < conf->nocaches->nelts; i++) {

	if ((ncent[i].name != NULL && strstr(desthost, ncent[i].name) != NULL)

	    || destaddr.s_addr == ncent[i].addr.s_addr || ncent[i].name[0] == '*')

	    nocache = 1;

