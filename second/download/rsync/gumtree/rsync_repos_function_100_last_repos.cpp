void send_filter_list(int f_out)
{
	int receiver_wants_list = prune_empty_dirs
	    || (delete_mode && (!delete_excluded || protocol_version >= 29));

	if (local_server || (am_sender && !receiver_wants_list))
		f_out = -1;
	if (cvs_exclude && am_sender) {
		if (protocol_version >= 29)
			parse_filter_str(&filter_list, ":C", rule_template(0), 0);
		parse_filter_str(&filter_list, "-C", rule_template(0), 0);
	}

	send_rules(f_out, &filter_list);

	if (f_out >= 0)
		write_int(f_out, 0);

	if (cvs_exclude) {
		if (!am_sender || protocol_version < 29)
			parse_filter_str(&filter_list, ":C", rule_template(0), 0);
		if (!am_sender)
			parse_filter_str(&filter_list, "-C", rule_template(0), 0);
	}
}