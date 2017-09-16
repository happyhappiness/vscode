    if (i == -1) {

	ap_kill_timeout(r);

	return ap_proxyerror(r, "Error reading from remote server");

    }

    if (i != 220) {

	ap_kill_timeout(r);

	return HTTP_BAD_GATEWAY;

    }



    Explain0("FTP: connected.");



    ap_bputs("USER ", f);

    ap_bwrite(f, user, userlen);

