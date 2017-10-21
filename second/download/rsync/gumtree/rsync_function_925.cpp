void parse_filter_str(filter_rule_list *listp, const char *rulestr,
		     const filter_rule *template, int xflags)
{
	filter_rule *rule;
	const char *pat;
	unsigned int pat_len;

	if (!rulestr)
		return;

	while (1) {
		uint32 new_rflags;

		/* Remember that the returned string is NOT '\0' terminated! */
		if (!(rule = parse_rule_tok(&rulestr, template, xflags, &pat, &pat_len)))
			break;

		if (pat_len >= MAXPATHLEN) {
			rprintf(FERROR, "discarding over-long filter: %.*s\n",
				(int)pat_len, pat);
		    free_continue:
			free_filter(rule);
			continue;
		}

		new_rflags = rule->rflags;
		if (new_rflags & FILTRULE_CLEAR_LIST) {
			if (DEBUG_GTE(FILTER, 2)) {
				rprintf(FINFO,
					"[%s] clearing filter list%s\n",
					who_am_i(), listp->debug_type);
			}
			clear_filter_list(listp);
			goto free_continue;
		}

		if (new_rflags & FILTRULE_MERGE_FILE) {
			if (!pat_len) {
				pat = ".cvsignore";
				pat_len = 10;
			}
			if (new_rflags & FILTRULE_EXCLUDE_SELF) {
				const char *name;
				filter_rule *excl_self;

				if (!(excl_self = new0(filter_rule)))
					out_of_memory("parse_filter_str");
				/* Find the beginning of the basename and add an exclude for it. */
				for (name = pat + pat_len; name > pat && name[-1] != '/'; name--) {}
				add_rule(listp, name, (pat + pat_len) - name, excl_self, 0);
				rule->rflags &= ~FILTRULE_EXCLUDE_SELF;
			}
			if (new_rflags & FILTRULE_PERDIR_MERGE) {
				if (parent_dirscan) {
					const char *p;
					unsigned int len = pat_len;
					if ((p = parse_merge_name(pat, &len, module_dirlen)))
						add_rule(listp, p, len, rule, 0);
					else
						free_filter(rule);
					continue;
				}
			} else {
				const char *p;
				unsigned int len = pat_len;
				if ((p = parse_merge_name(pat, &len, 0)))
					parse_filter_file(listp, p, rule, XFLG_FATAL_ERRORS);
				free_filter(rule);
				continue;
			}
		}

		add_rule(listp, pat, pat_len, rule, xflags);

		if (new_rflags & FILTRULE_CVS_IGNORE
		    && !(new_rflags & FILTRULE_MERGE_FILE))
			get_cvs_excludes(new_rflags);
	}
}