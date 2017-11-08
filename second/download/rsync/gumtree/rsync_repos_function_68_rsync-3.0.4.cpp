void parse_rule(struct filter_list_struct *listp, const char *pattern,
		uint32 mflags, int xflags)
{
	unsigned int pat_len;
	uint32 new_mflags;
	const char *cp, *p;

	if (!pattern)
		return;

	while (1) {
		/* Remember that the returned string is NOT '\0' terminated! */
		cp = parse_rule_tok(pattern, mflags, xflags,
				    &pat_len, &new_mflags);
		if (!cp)
			break;

		pattern = cp + pat_len;

		if (pat_len >= MAXPATHLEN) {
			rprintf(FERROR, "discarding over-long filter: %.*s\n",
				(int)pat_len, cp);
			continue;
		}

		if (new_mflags & MATCHFLG_CLEAR_LIST) {
			if (verbose > 2) {
				rprintf(FINFO,
					"[%s] clearing filter list%s\n",
					who_am_i(), listp->debug_type);
			}
			clear_filter_list(listp);
			continue;
		}

		if (new_mflags & MATCHFLG_MERGE_FILE) {
			unsigned int len;
			if (!pat_len) {
				cp = ".cvsignore";
				pat_len = 10;
			}
			len = pat_len;
			if (new_mflags & MATCHFLG_EXCLUDE_SELF) {
				const char *name = cp + len;
				while (name > cp && name[-1] != '/') name--;
				len -= name - cp;
				add_rule(listp, name, len, 0, 0);
				new_mflags &= ~MATCHFLG_EXCLUDE_SELF;
				len = pat_len;
			}
			if (new_mflags & MATCHFLG_PERDIR_MERGE) {
				if (parent_dirscan) {
					if (!(p = parse_merge_name(cp, &len,
								module_dirlen)))
						continue;
					add_rule(listp, p, len, new_mflags, 0);
					continue;
				}
			} else {
				if (!(p = parse_merge_name(cp, &len, 0)))
					continue;
				parse_filter_file(listp, p, new_mflags,
						  XFLG_FATAL_ERRORS);
				continue;
			}
		}

		add_rule(listp, cp, pat_len, new_mflags, xflags);

		if (new_mflags & MATCHFLG_CVS_IGNORE
		    && !(new_mflags & MATCHFLG_MERGE_FILE))
			get_cvs_excludes(new_mflags);
	}
}