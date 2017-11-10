struct commit_list *get_octopus_merge_bases(struct commit_list *in)
{
	struct commit_list *i, *j, *k, *ret = NULL;

	if (!in)
		return ret;

	commit_list_insert(in->item, &ret);

	for (i = in->next; i; i = i->next) {
		struct commit_list *new = NULL, *end = NULL;

		for (j = ret; j; j = j->next) {
			struct commit_list *bases;
			bases = get_merge_bases(i->item, j->item);
			if (!new)
				new = bases;
			else
				end->next = bases;
			for (k = bases; k; k = k->next)
				end = k;
		}
		ret = new;
	}
	return ret;
}