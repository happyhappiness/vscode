    dsock = ap_psocket(p, PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (dsock == -1) {
	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		     "proxy: error creating PASV socket");
	ap_bclose(f);
	ap_kill_timeout(r);
	return SERVER_ERROR;
    }

    if (conf->recv_buffer_size) {
	if (setsockopt(dsock, SOL_SOCKET, SO_RCVBUF,
	       (const char *) &conf->recv_buffer_size, sizeof(int)) == -1) {
	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
