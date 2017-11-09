static int exchange_protocols(int f_in, int f_out, char *buf, size_t bufsiz, int am_client)
{
	int remote_sub = -1;
#if SUBPROTOCOL_VERSION != 0
	int our_sub = protocol_version < PROTOCOL_VERSION ? 0 : SUBPROTOCOL_VERSION;
#else
	int our_sub = 0;
#endif
	char *motd;

	io_printf(f_out, "@RSYNCD: %d.%d\n", protocol_version, our_sub);

	if (!am_client) {
		motd = lp_motd_file();
		if (motd && *motd) {
			FILE *f = fopen(motd,"r");
			while (f && !feof(f)) {
				int len = fread(buf, 1, bufsiz - 1, f);
				if (len > 0)
					write_buf(f_out, buf, len);
			}
			if (f)
				fclose(f);
			write_sbuf(f_out, "\n");
		}
	}

	/* This strips the \n. */
	if (!read_line_old(f_in, buf, bufsiz, 0)) {
		if (am_client)
			rprintf(FERROR, "rsync: did not see server greeting\n");
		return -1;
	}

	if (sscanf(buf, "@RSYNCD: %d.%d", &remote_protocol, &remote_sub) < 1) {
		if (am_client)
			rprintf(FERROR, "rsync: server sent \"%s\" rather than greeting\n", buf);
		else
			io_printf(f_out, "@ERROR: protocol startup error\n");
		return -1;
	}

	if (remote_sub < 0) {
		if (remote_protocol == 30) {
			if (am_client)
				rprintf(FERROR, "rsync: server is speaking an incompatible beta of protocol 30\n");
			else
				io_printf(f_out, "@ERROR: your client is speaking an incompatible beta of protocol 30\n");
			return -1;
		}
		remote_sub = 0;
	}

	if (protocol_version > remote_protocol) {
		protocol_version = remote_protocol;
		if (remote_sub)
			protocol_version--;
	} else if (protocol_version == remote_protocol) {
		if (remote_sub != our_sub)
			protocol_version--;
	}
#if SUBPROTOCOL_VERSION != 0
	else if (protocol_version < remote_protocol) {
		if (our_sub)
			protocol_version--;
	}
#endif

	if (protocol_version >= 30)
		rl_nulls = 1;

	return 0;
}