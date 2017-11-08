int check_exclude(char *name, struct exclude_struct **local_exclude_list,
		  STRUCT_STAT *st)
{
	int n;
        struct exclude_struct *ent;

	if (name && (name[0] == '.') && !name[1])
		/* never exclude '.', even if somebody does --exclude '*' */
		return 0;

	if (exclude_list) {
		for (n=0; exclude_list[n]; n++) {
                        ent = exclude_list[n];
			if (check_one_exclude(name, ent, st)) {
                                report_exclude_result(name, ent, st);
				return !ent->include;
                        }
                }
	}

	if (local_exclude_list) {
		for (n=0; local_exclude_list[n]; n++) {
                        ent = local_exclude_list[n];
			if (check_one_exclude(name, ent, st)) {
                                report_exclude_result(name, ent, st);
				return !ent->include;
                        }
                }
	}

	return 0;
}