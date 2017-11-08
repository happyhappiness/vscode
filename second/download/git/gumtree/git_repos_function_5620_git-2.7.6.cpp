static void add_sought_entry(struct ref ***sought, int *nr, int *alloc,
			     const char *name)
{
	struct ref *ref;
	struct object_id oid;

	if (!get_oid_hex(name, &oid) && name[GIT_SHA1_HEXSZ] == ' ')
		name += GIT_SHA1_HEXSZ + 1;
	else
		oidclr(&oid);

	ref = alloc_ref(name);
	oidcpy(&ref->old_oid, &oid);
	(*nr)++;
	ALLOC_GROW(*sought, *nr, *alloc);
	(*sought)[*nr - 1] = ref;
}