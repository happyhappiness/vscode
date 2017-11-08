static void filter_refs(struct fetch_pack_args *args,
			struct ref **refs,
			struct ref **sought, int nr_sought)
{
	struct ref *newlist = NULL;
	struct ref **newtail = &newlist;
	struct ref *ref, *next;
	int i;

	i = 0;
	for (ref = *refs; ref; ref = next) {
		int keep = 0;
		next = ref->next;

		if (starts_with(ref->name, "refs/") &&
		    check_refname_format(ref->name, 0))
			; /* trash */
		else {
			while (i < nr_sought) {
				int cmp = strcmp(ref->name, sought[i]->name);
				if (cmp < 0)
					break; /* definitely do not have it */
				else if (cmp == 0) {
					keep = 1; /* definitely have it */
					sought[i]->matched = 1;
				}
				i++;
			}
		}

		if (!keep && args->fetch_all &&
		    (!args->depth || !starts_with(ref->name, "refs/tags/")))
			keep = 1;

		if (keep) {
			*newtail = ref;
			ref->next = NULL;
			newtail = &ref->next;
		} else {
			free(ref);
		}
	}

	/* Append unmatched requests to the list */
	if (allow_tip_sha1_in_want) {
		for (i = 0; i < nr_sought; i++) {
			ref = sought[i];
			if (ref->matched)
				continue;
			if (get_sha1_hex(ref->name, ref->old_sha1))
				continue;

			ref->matched = 1;
			*newtail = ref;
			ref->next = NULL;
			newtail = &ref->next;
		}
	}
	*refs = newlist;
}