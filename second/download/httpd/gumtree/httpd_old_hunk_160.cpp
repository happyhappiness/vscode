		    return HTTP_BAD_GATEWAY;
		}
		path = "";
		len = 0;
	    }
	    else if (i == 213) { /* Size command ok */
		for (j = 0; j < resplen && ap_isdigit(resp[j]); j++)
			;
		resp[j] = '\0';
		if (resp[0] != '\0')
		    size = ap_pstrdup(p, resp);
	    }
	}
    }

    if (parms[0] == 'd') {
	if (len != 0)
	    ap_bputs("LIST ", f);
	else
	    ap_bputs("LIST -lag", f);
	Explain1("FTP: LIST %s", (len == 0 ? "" : path));
    }
    else {
	ap_bputs("RETR ", f);
	Explain1("FTP: RETR %s", path);
    }
    ap_bwrite(f, path, len);
    ap_bputs(CRLF, f);
    ap_bflush(f);
/* RETR: 110, 125, 150, 226, 250, 421, 425, 426, 450, 451, 500, 501, 530, 550
   NLST: 125, 150, 226, 250, 421, 425, 426, 450, 451, 500, 501, 502, 530 */
    rc = ftp_getrc(f);
    Explain1("FTP: returned status %d", rc);
    if (rc == -1) {
	ap_kill_timeout(r);
	return ap_proxyerror(r, "Error sending to remote server");
    }
    if (rc == 550) {
	Explain0("FTP: RETR failed, trying LIST instead");
	parms = "d";
	ap_bputs("CWD ", f);
	ap_bwrite(f, path, len);
	ap_bputs(CRLF, f);
	ap_bflush(f);
	Explain1("FTP: CWD %s", path);
	rc = ftp_getrc(f);
	Explain1("FTP: returned status %d", rc);
	if (rc == -1) {
	    ap_kill_timeout(r);
	    return ap_proxyerror(r, "Error sending to remote server");
	}
	if (rc == 550) {
	    ap_kill_timeout(r);
	    return HTTP_NOT_FOUND;
	}
	if (rc != 250) {
	    ap_kill_timeout(r);
	    return HTTP_BAD_GATEWAY;
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
	return HTTP_BAD_GATEWAY;

    r->status = 200;
    r->status_line = "200 OK";

    resp_hdrs = ap_make_array(p, 2, sizeof(struct hdr_entry));
    c->hdrs = resp_hdrs;

    if (parms[0] == 'd')
	ap_proxy_add_header(resp_hdrs, "Content-Type", "text/html", HDR_REP);
    else {
	if (r->content_type != NULL) {
	    ap_proxy_add_header(resp_hdrs, "Content-Type", r->content_type,
			     HDR_REP);
	    Explain1("FTP: Content-Type set to %s", r->content_type);
	}
	else {
	    ap_proxy_add_header(resp_hdrs, "Content-Type", "text/plain", HDR_REP);
	}
	if (parms[0] != 'a' && size != NULL) {
	    ap_proxy_add_header(resp_hdrs, "Content-Length", size, HDR_REP);
	    Explain1("FTP: Content-Length set to %s", size);
	}
    }

/* check if NoCache directive on this host */
    for (i = 0; i < conf->nocaches->nelts; i++) {
