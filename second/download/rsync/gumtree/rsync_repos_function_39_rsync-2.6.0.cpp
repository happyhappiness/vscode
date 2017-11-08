int check_exclude(struct exclude_struct **list, char *name, int name_is_dir)
{
	struct exclude_struct *ent;

	while ((ent = *list++) != NULL) {
		if (check_one_exclude(name, ent, name_is_dir)) {
			report_exclude_result(name, ent, name_is_dir);
			return !ent->include;
		}
	}

	return 0;
}