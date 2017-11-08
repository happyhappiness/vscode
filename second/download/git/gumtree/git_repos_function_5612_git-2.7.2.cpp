static void add_sought_entry_mem(struct ref ***sought, int *nr, int *alloc,
				 const char *name, int namelen)
{
	struct ref *ref = xcalloc(1, sizeof(*ref) + namelen + 1);
	struct object_id oid;
	const int chunksz = GIT_SHA1_HEXSZ + 1;

	if (namelen > chunksz && name[chunksz - 1] == ' ' &&
		!get_oid_hex(name, &oid)) {
		oidcpy(&ref->old_oid, &oid);
		name += chunksz;
		namelen -= chunksz;
	}

	memcpy(ref->name, name, namelen);
	ref->name[namelen] = '\0';
	(*nr)++;
	ALLOC_GROW(*sought, *nr, *alloc);
	(*sought)[*nr - 1] = ref;
}