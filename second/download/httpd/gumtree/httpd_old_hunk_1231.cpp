	r->status_line = ap_pstrdup(p, &buffer[9]);



/* read the headers. */

/* N.B. for HTTP/1.0 clients, we have to fold line-wrapped headers */

/* Also, take care with headers with multiple occurences. */



	resp_hdrs = ap_proxy_read_headers(p, buffer, HUGE_STRING_LEN, f);



	clear_connection(p, (table *) resp_hdrs);	/* Strip Connection hdrs */

    }

    else {

/* an http/0.9 response */

	backasswards = 1;

	r->status = 200;

	r->status_line = "200 OK";



/* no headers */

	resp_hdrs = ap_make_array(p, 2, sizeof(struct hdr_entry));

    }



    c->hdrs = resp_hdrs;



    ap_kill_timeout(r);



/*

 * HTTP/1.0 requires us to accept 3 types of dates, but only generate

 * one type

 */



    hdr = (struct hdr_entry *) resp_hdrs->elts;

    for (i = 0; i < resp_hdrs->nelts; i++) {

	if (hdr[i].value[0] == '\0')

	    continue;

	strp = hdr[i].field;

	if (strcasecmp(strp, "Date") == 0 ||

	    strcasecmp(strp, "Last-Modified") == 0 ||

	    strcasecmp(strp, "Expires") == 0)

	    hdr[i].value = ap_proxy_date_canon(p, hdr[i].value);

	if (strcasecmp(strp, "Location") == 0 ||

	    strcasecmp(strp, "URI") == 0)

	    hdr[i].value = proxy_location_reverse_map(r, hdr[i].value);

    }



/* check if NoCache directive on this host */

    for (i = 0; i < conf->nocaches->nelts; i++) {

	if ((ncent[i].name != NULL && strstr(desthost, ncent[i].name) != NULL)

	    || destaddr.s_addr == ncent[i].addr.s_addr || ncent[i].name[0] == '*')

	    nocache = 1;

