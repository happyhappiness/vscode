static void send_rules(int f_out, struct filter_list_struct *flp)
{
	struct filter_struct *ent, *prev = NULL;

	for (ent = flp->head; ent; ent = ent->next) {
		unsigned int len, plen, dlen;
		int elide = 0;
		char *p;

		if (ent->match_flags & MATCHFLG_SENDER_SIDE)
			elide = am_sender ? 1 : -1;
		if (ent->match_flags & MATCHFLG_RECEIVER_SIDE)
			elide = elide ? 0 : am_sender ? -1 : 1;
		else if (delete_excluded && !elide)
			elide = am_sender ? 1 : -1;
		if (elide < 0) {
			if (prev)
				prev->next = ent->next;
			else
				flp->head = ent->next;
		} else
			prev = ent;
		if (elide > 0)
			continue;
		if (ent->match_flags & MATCHFLG_CVS_IGNORE
		    && !(ent->match_flags & MATCHFLG_MERGE_FILE)) {
			int f = am_sender || protocol_version < 29 ? f_out : -2;
			send_rules(f, &cvs_filter_list);
			if (f == f_out)
				continue;
		}
		p = get_rule_prefix(ent->match_flags, ent->pattern, 1, &plen);
		if (!p) {
			rprintf(FERROR,
				"filter rules are too modern for remote rsync.\n");
			exit_cleanup(RERR_SYNTAX);
		}
		if (f_out < 0)
			continue;
		len = strlen(ent->pattern);
		dlen = ent->match_flags & MATCHFLG_DIRECTORY ? 1 : 0;
		if (!(plen + len + dlen))
			continue;
		write_int(f_out, plen + len + dlen);
		if (plen)
			write_buf(f_out, p, plen);
		write_buf(f_out, ent->pattern, len);
		if (dlen)
			write_byte(f_out, '/');
	}
	flp->tail = prev;
}