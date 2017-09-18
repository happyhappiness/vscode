    f = ap_bcreate(p, B_RDWR | B_SOCKET);
    ap_bpushfd(f, sock, sock);

    ap_hard_timeout("proxy send", r);
    ap_bvputs(f, r->method, " ", proxyhost ? url : urlptr, " HTTP/1.0" CRLF,
	   NULL);
    if (destportstr != NULL && destport != DEFAULT_HTTP_PORT)
	ap_bvputs(f, "Host: ", desthost, ":", destportstr, CRLF, NULL);
    else
	ap_bvputs(f, "Host: ", desthost, CRLF, NULL);

    if (conf->viaopt == via_block) {
	/* Block all outgoing Via: headers */
	ap_table_unset(r->headers_in, "Via");
    } else if (conf->viaopt != via_off) {
	/* Create a "Via:" request header entry and merge it */
	i = ap_get_server_port(r);
	if (ap_is_default_port(i,r)) {
	    strcpy(portstr,"");
	} else {
	    ap_snprintf(portstr, sizeof portstr, ":%d", i);
	}
	/* Generate outgoing Via: header with/without server comment: */
	ap_table_mergen(r->headers_in, "Via",
		    (conf->viaopt == via_full)
			? ap_psprintf(p, "%d.%d %s%s (%s)",
				HTTP_VERSION_MAJOR(r->proto_num),
				HTTP_VERSION_MINOR(r->proto_num),
				ap_get_server_name(r), portstr,
				SERVER_BASEVERSION)
			: ap_psprintf(p, "%d.%d %s%s",
				HTTP_VERSION_MAJOR(r->proto_num),
				HTTP_VERSION_MINOR(r->proto_num),
				ap_get_server_name(r), portstr)
			);
    }

    reqhdrs_arr = ap_table_elts(r->headers_in);
    reqhdrs = (table_entry *) reqhdrs_arr->elts;
    for (i = 0; i < reqhdrs_arr->nelts; i++) {
	if (reqhdrs[i].key == NULL || reqhdrs[i].val == NULL
	/* Clear out headers not to send */
	    || !strcasecmp(reqhdrs[i].key, "Host")	/* Already sent */
	    /* XXX: @@@ FIXME: "Proxy-Authorization" should *only* be 
	     * suppressed if THIS server requested the authentication,
	     * not when a frontend proxy requested it!
	     */
	    || !strcasecmp(reqhdrs[i].key, "Proxy-Authorization"))
	    continue;
	ap_bvputs(f, reqhdrs[i].key, ": ", reqhdrs[i].val, CRLF, NULL);
    }

    ap_bputs(CRLF, f);
/* send the request data, if any. N.B. should we trap SIGPIPE ? */

    if (ap_should_client_block(r)) {
	while ((i = ap_get_client_block(r, buffer, sizeof buffer)) > 0)
	    ap_bwrite(f, buffer, i);
    }
    ap_bflush(f);
    ap_kill_timeout(r);

    ap_hard_timeout("proxy receive", r);

    len = ap_bgets(buffer, sizeof buffer - 1, f);
    if (len == -1 || len == 0) {
	ap_bclose(f);
	ap_kill_timeout(r);
	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		     "ap_bgets() - proxy receive - Error reading from remote server %s",
		     proxyhost ? proxyhost : desthost);
	return ap_proxyerror(r, "Error reading from remote server");
    }

/* Is it an HTTP/1 response?  This is buggy if we ever see an HTTP/1.10 */
    if (ap_checkmask(buffer, "HTTP/#.# ###*")) {
	int major, minor;
	if (2 != sscanf(buffer, "HTTP/%u.%u", &major, &minor)) {
	    major = 1;
	    minor = 0;
	}

/* If not an HTTP/1 message or if the status line was > 8192 bytes */
	if (buffer[5] != '1' || buffer[len - 1] != '\n') {
	    ap_bclose(f);
	    ap_kill_timeout(r);
	    return HTTP_BAD_GATEWAY;
	}
	backasswards = 0;
