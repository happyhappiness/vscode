static int write_out_results(struct patch *list)
{
	int phase;
	int errs = 0;
	struct patch *l;
	struct string_list cpath = STRING_LIST_INIT_DUP;

	for (phase = 0; phase < 2; phase++) {
		l = list;
		while (l) {
			if (l->rejected)
				errs = 1;
			else {
				write_out_one_result(l, phase);
				if (phase == 1) {
					if (write_out_one_reject(l))
						errs = 1;
					if (l->conflicted_threeway) {
						string_list_append(&cpath, l->new_name);
						errs = 1;
					}
				}
			}
			l = l->next;
		}
	}

	if (cpath.nr) {
		struct string_list_item *item;

		sort_string_list(&cpath);
		for_each_string_list_item(item, &cpath)
			fprintf(stderr, "U %s\n", item->string);
		string_list_clear(&cpath, 0);

		rerere(0);
	}

	return errs;
}