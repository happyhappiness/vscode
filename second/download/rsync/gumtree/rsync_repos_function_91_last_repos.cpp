int check_filter(filter_rule_list *listp, enum logcode code,
		 const char *name, int name_is_dir)
{
	filter_rule *ent;

	for (ent = listp->head; ent; ent = ent->next) {
		if (ignore_perishable && ent->rflags & FILTRULE_PERISHABLE)
			continue;
		if (ent->rflags & FILTRULE_PERDIR_MERGE) {
			int rc = check_filter(ent->u.mergelist, code, name,
					      name_is_dir);
			if (rc)
				return rc;
			continue;
		}
		if (ent->rflags & FILTRULE_CVS_IGNORE) {
			int rc = check_filter(&cvs_filter_list, code, name,
					      name_is_dir);
			if (rc)
				return rc;
			continue;
		}
		if (rule_matches(name, ent, name_is_dir)) {
			report_filter_result(code, name, ent, name_is_dir,
					     listp->debug_type);
			return ent->rflags & FILTRULE_INCLUDE ? 1 : -1;
		}
	}

	return 0;
}