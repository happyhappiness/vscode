void setup_protocol(int f_out,int f_in)
{
	if (remote_protocol == 0) {
		if (am_server) {
			remote_protocol = read_int(f_in);
			write_int(f_out, protocol_version);
		} else {
			write_int(f_out, protocol_version);
			remote_protocol = read_int(f_in);
		}
		if (protocol_version > remote_protocol)
			protocol_version = remote_protocol;
	}

	if (verbose > 3) {
		rprintf(FINFO, "(%s) Protocol versions: remote=%d, negotiated=%d\n",
			am_server? "Server" : "Client", remote_protocol, protocol_version);
	}
	if (remote_protocol < MIN_PROTOCOL_VERSION
	 || remote_protocol > MAX_PROTOCOL_VERSION) {
		rprintf(FERROR,"protocol version mismatch - is your shell clean?\n");
		rprintf(FERROR,"(see the rsync man page for an explanation)\n");
		exit_cleanup(RERR_PROTOCOL);
	}
	if (remote_protocol < OLD_PROTOCOL_VERSION) {
		rprintf(FINFO,"%s is very old version of rsync, upgrade recommended.\n",
			am_server? "Client" : "Server");
	}
	if (protocol_version < MIN_PROTOCOL_VERSION) {
		rprintf(FERROR, "--protocol must be at least %d on the %s.\n",
			MIN_PROTOCOL_VERSION, am_server? "Server" : "Client");
		exit_cleanup(RERR_PROTOCOL);
	}
	if (protocol_version > PROTOCOL_VERSION) {
		rprintf(FERROR, "--protocol must be no more than %d on the %s.\n",
			PROTOCOL_VERSION, am_server? "Server" : "Client");
		exit_cleanup(RERR_PROTOCOL);
	}

	if (am_server) {
		if (!checksum_seed)
			checksum_seed = time(NULL);
		write_int(f_out, checksum_seed);
	} else {
		checksum_seed = read_int(f_in);
	}
}