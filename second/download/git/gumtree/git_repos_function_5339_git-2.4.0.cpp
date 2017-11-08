static void add_sought_entry_mem(struct ref ***sought, int *nr, int *alloc,
				 const char *name, int namelen)
{
	struct ref *ref = xcalloc(1, sizeof(*ref) + namelen + 1);
	unsigned char sha1[20];

	if (namelen > 41 && name[40] == ' ' && !get_sha1_hex(name, sha1)) {
		hashcpy(ref->old_sha1, sha1);
		name += 41;
		namelen -= 41;
	}

	memcpy(ref->name, name, namelen);
	ref->name[namelen] = '\0';
	(*nr)++;
	ALLOC_GROW(*sought, *nr, *alloc);
	(*sought)[*nr - 1] = ref;
}