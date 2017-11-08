void send_filter_list(int f_out)
{
	int receiver_wants_list = delete_mode
		&& (!delete_excluded || protocol_version >= 29);

	if (local_server || (am_sender && !receiver_wants_list))
		f_out = -1;
	if (cvs_exclude && am_sender) {
		if (protocol_version >= 29)
			parse_rule(&filter_list, ":C", 0, 0);
		parse_rule(&filter_list, "-C", 0, 0);
	}

	/* This is a complete hack - blame Rusty.  FIXME!
	 * Remove this hack when older rsyncs (below 2.6.4) are gone. */
	if (list_only == 1 && !recurse)
		parse_rule(&filter_list, "/*/*", MATCHFLG_NO_PREFIXES, 0);

	send_rules(f_out, &filter_list);

	if (f_out >= 0)
		write_int(f_out, 0);

	if (cvs_exclude) {
		if (!am_sender || protocol_version < 29)
			parse_rule(&filter_list, ":C", 0, 0);
		if (!am_sender)
			parse_rule(&filter_list, "-C", 0, 0);
	}
}