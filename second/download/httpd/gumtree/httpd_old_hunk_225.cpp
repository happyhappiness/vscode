	if (rc == -1) {

	    ap_kill_timeout(r);

	    return ap_proxyerror(r, "Error sending to remote server");

	}

	if (rc == 550) {

	    ap_kill_timeout(r);

	    return NOT_FOUND;

	}

	if (rc != 250) {

	    ap_kill_timeout(r);

	    return BAD_GATEWAY;

	}



	ap_bputs("LIST -lag" CRLF, f);

	ap_bflush(f);

	Explain0("FTP: LIST -lag");

	rc = ftp_getrc(f);

	Explain1("FTP: returned status %d", rc);

	if (rc == -1)

	    return ap_proxyerror(r, "Error sending to remote server");

    }

    ap_kill_timeout(r);

    if (rc != 125 && rc != 150 && rc != 226 && rc != 250)

	return BAD_GATEWAY;



    r->status = 200;

    r->status_line = "200 OK";



    resp_hdrs = ap_make_array(p, 2, sizeof(struct hdr_entry));

    if (parms[0] == 'd')

	ap_proxy_add_header(resp_hdrs, "Content-Type", "text/html", HDR_REP);

    else {

	if (r->content_type != NULL) {

	    ap_proxy_add_header(resp_hdrs, "Content-Type", r->content_type,

			     HDR_REP);

