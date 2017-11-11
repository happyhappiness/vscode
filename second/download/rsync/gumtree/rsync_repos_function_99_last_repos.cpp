static void send_rules(int f_out, filter_rule_list *flp)
{
	filter_rule *ent, *prev = NULL;

	for (ent = flp->head; ent; ent = ent->next) {
		unsigned int len, plen, dlen;
		int elide = 0;
		char *p;

		/* Note we need to check delete_excluded here in addition to
		 * the code in parse_rule_tok() because some rules may have
		 * been added before we found the --delete-excluded option.
		 * We must also elide any CVS merge-file rules to avoid a
		 * backward compatibility problem, and we elide any no-prefix
		 * merge files as an optimization (since they can only have
		 * include/exclude rules). */
		if (ent->rflags & FILTRULE_SENDER_SIDE)
			elide = am_sender ? 1 : -1;
		if (ent->rflags & FILTRULE_RECEIVER_SIDE)
			elide = elide ? 0 : am_sender ? -1 : 1;
		else if (delete_excluded && !elide
		 && (!(ent->rflags & FILTRULE_PERDIR_MERGE)
		  || ent->rflags & FILTRULE_NO_PREFIXES))
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
		if (ent->rflags & FILTRULE_CVS_IGNORE
		    && !(ent->rflags & FILTRULE_MERGE_FILE)) {
			int f = am_sender || protocol_version < 29 ? f_out : -2;
			send_rules(f, &cvs_filter_list);
			if (f == f_out)
				continue;
		}
		p = get_rule_prefix(ent, ent->pattern, 1, &plen);
		if (!p) {
			rprintf(FERROR,
				"filter rules are too modern for remote rsync.\n");
			exit_cleanup(RERR_PROTOCOL);
		}
		if (f_out < 0)
			continue;
		len = strlen(ent->pattern);
		dlen = ent->rflags & FILTRULE_DIRECTORY ? 1 : 0;
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