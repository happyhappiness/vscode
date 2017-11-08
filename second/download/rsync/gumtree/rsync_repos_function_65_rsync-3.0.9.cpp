int check_filter(struct filter_list_struct *listp, enum logcode code,
		 const char *name, int name_is_dir)
{
	struct filter_struct *ent;

	for (ent = listp->head; ent; ent = ent->next) {
		if (ignore_perishable && ent->match_flags & MATCHFLG_PERISHABLE)
			continue;
		if (ent->match_flags & MATCHFLG_PERDIR_MERGE) {
			int rc = check_filter(ent->u.mergelist, code, name,
					      name_is_dir);
			if (rc)
				return rc;
			continue;
		}
		if (ent->match_flags & MATCHFLG_CVS_IGNORE) {
			int rc = check_filter(&cvs_filter_list, code, name,
					      name_is_dir);
			if (rc)
				return rc;
			continue;
		}
		if (rule_matches(name, ent, name_is_dir)) {
			report_filter_result(code, name, ent, name_is_dir,
					     listp->debug_type);
			return ent->match_flags & MATCHFLG_INCLUDE ? 1 : -1;
		}
	}

	return 0;
}