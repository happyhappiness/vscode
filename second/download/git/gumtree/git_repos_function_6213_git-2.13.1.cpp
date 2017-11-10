static void add_sought_entry(struct ref ***sought, int *nr, int *alloc,
			     const char *name)
{
	struct ref *ref;
	struct object_id oid;

	if (!get_oid_hex(name, &oid)) {
		if (name[GIT_SHA1_HEXSZ] == ' ') {
			/* <sha1> <ref>, find refname */
			name += GIT_SHA1_HEXSZ + 1;
		} else if (name[GIT_SHA1_HEXSZ] == '\0') {
			; /* <sha1>, leave sha1 as name */
		} else {
			/* <ref>, clear cruft from oid */
			oidclr(&oid);
		}
	} else {
		/* <ref>, clear cruft from get_oid_hex */
		oidclr(&oid);
	}

	ref = alloc_ref(name);
	oidcpy(&ref->old_oid, &oid);
	(*nr)++;
	ALLOC_GROW(*sought, *nr, *alloc);
	(*sought)[*nr - 1] = ref;
}