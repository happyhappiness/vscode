    f = ap_bcreate(p, B_RDWR | B_SOCKET);

    ap_bpushfd(f, sock, sock);



    ap_hard_timeout("proxy send", r);

    ap_bvputs(f, r->method, " ", proxyhost ? url : urlptr, " HTTP/1.0" CRLF,

	   NULL);

    ap_bvputs(f, "Host: ", desthost, NULL);

    if (destportstr != NULL && destport != DEFAULT_HTTP_PORT)

	ap_bvputs(f, ":", destportstr, CRLF, NULL);

    else

	ap_bputs(CRLF, f);



    reqhdrs_arr = ap_table_elts(r->headers_in);

    reqhdrs = (table_entry *) reqhdrs_arr->elts;

    for (i = 0; i < reqhdrs_arr->nelts; i++) {

	if (reqhdrs[i].key == NULL || reqhdrs[i].val == NULL

	/* Clear out headers not to send */

	    || !strcasecmp(reqhdrs[i].key, "Host")	/* Already sent */

	    ||!strcasecmp(reqhdrs[i].key, "Proxy-Authorization"))

	    continue;

	ap_bvputs(f, reqhdrs[i].key, ": ", reqhdrs[i].val, CRLF, NULL);

    }



    ap_bputs(CRLF, f);

/* send the request data, if any. N.B. should we trap SIGPIPE ? */



    if (ap_should_client_block(r)) {

	while ((i = ap_get_client_block(r, buffer, HUGE_STRING_LEN)) > 0)

	    ap_bwrite(f, buffer, i);

    }

    ap_bflush(f);

    ap_kill_timeout(r);



    ap_hard_timeout("proxy receive", r);



    len = ap_bgets(buffer, HUGE_STRING_LEN - 1, f);

    if (len == -1 || len == 0) {

	ap_bclose(f);

	ap_kill_timeout(r);

	return ap_proxyerror(r, "Error reading from remote server");

    }



/* Is it an HTTP/1 response?  This is buggy if we ever see an HTTP/1.10 */

    if (ap_checkmask(buffer, "HTTP/#.# ###*")) {

/* If not an HTTP/1 messsage or if the status line was > 8192 bytes */

	if (buffer[5] != '1' || buffer[len - 1] != '\n') {

	    ap_bclose(f);

	    ap_kill_timeout(r);

	    return HTTP_BAD_GATEWAY;

	}

	backasswards = 0;

