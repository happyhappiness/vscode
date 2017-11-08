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
					sought[i]->match_status = REF_MATCHED;
				}
				i++;
			}
		}

		if (!keep && args->fetch_all &&
		    (!args->deepen || !starts_with(ref->name, "refs/tags/")))
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
	for (i = 0; i < nr_sought; i++) {
		unsigned char sha1[20];

		ref = sought[i];
		if (ref->match_status != REF_NOT_MATCHED)
			continue;
		if (get_sha1_hex(ref->name, sha1) ||
		    ref->name[40] != '\0' ||
		    hashcmp(sha1, ref->old_oid.hash))
			continue;

		if ((allow_unadvertised_object_request &
		    (ALLOW_TIP_SHA1 | ALLOW_REACHABLE_SHA1))) {
			ref->match_status = REF_MATCHED;
			*newtail = copy_ref(ref);
			newtail = &(*newtail)->next;
		} else {
			ref->match_status = REF_UNADVERTISED_NOT_ALLOWED;
		}
	}
	*refs = newlist;
}