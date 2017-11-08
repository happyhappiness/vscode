int check_exclude(char *name,struct exclude_struct **local_exclude_list,
		  STRUCT_STAT *st)
{
	int n;

	if (exclude_list) {
		for (n=0; exclude_list[n]; n++)
			if (check_one_exclude(name,exclude_list[n],st))
				return !exclude_list[n]->include;
	}

	if (local_exclude_list) {
		for (n=0; local_exclude_list[n]; n++)
			if (check_one_exclude(name,local_exclude_list[n],st))
				return !local_exclude_list[n]->include;
	}

	return 0;
}