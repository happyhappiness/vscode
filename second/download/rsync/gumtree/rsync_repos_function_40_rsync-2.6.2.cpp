int check_exclude(struct exclude_list_struct *listp, char *name, int name_is_dir)
{
	struct exclude_struct *ent;

	for (ent = listp->head; ent; ent = ent->next) {
		if (check_one_exclude(name, ent, name_is_dir)) {
			report_exclude_result(name, ent, name_is_dir,
					      listp->debug_type);
			return ent->include ? 1 : -1;
		}
	}

	return 0;
}