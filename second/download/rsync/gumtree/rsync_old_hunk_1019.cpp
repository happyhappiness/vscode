			cp = rule->pattern;

		/* If the local merge file was already mentioned, don't
		 * add it again. */
		for (i = 0; i < mergelist_cnt; i++) {
			filter_rule *ex = mergelist_parents[i];
			const char *s = strrchr(ex->pattern, '/');
			if (s)
				s++;
			else
				s = ex->pattern;
			len = strlen(s);
			if (len == pat_len - (cp - rule->pattern) && memcmp(s, cp, len) == 0) {
				free_filter(rule);
				return;
			}
		}

		if (!(lp = new_array(filter_rule_list, 1)))
			out_of_memory("add_rule");
		lp->head = lp->tail = lp->parent_dirscan_head = NULL;
		if (asprintf(&lp->debug_type, " [per-dir %s]", cp) < 0)
			out_of_memory("add_rule");
		rule->u.mergelist = lp;

		if (mergelist_cnt == mergelist_size) {
			mergelist_size += 5;
