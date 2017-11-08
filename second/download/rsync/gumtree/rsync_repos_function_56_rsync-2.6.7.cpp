void recv_filter_list(int f_in)
{
	char line[BIGPATHBUFLEN];
	int xflags = protocol_version >= 29 ? 0 : XFLG_OLD_PREFIXES;
	int receiver_wants_list = prune_empty_dirs
	    || (saw_delete_opt
	     && (!saw_delete_excluded_opt || protocol_version >= 29));
	unsigned int len;

	if (!local_server && (am_sender || receiver_wants_list)) {
		while ((len = read_int(f_in)) != 0) {
			if (len >= sizeof line)
				overflow_exit("recv_rules");
			read_sbuf(f_in, line, len);
			parse_rule(&filter_list, line, 0, xflags);
		}
	}

	if (cvs_exclude) {
		if (local_server || am_sender || protocol_version < 29)
			parse_rule(&filter_list, ":C", 0, 0);
		if (local_server || am_sender)
			parse_rule(&filter_list, "-C", 0, 0);
	}

	if (local_server) /* filter out any rules that aren't for us. */
		send_rules(-1, &filter_list);
}