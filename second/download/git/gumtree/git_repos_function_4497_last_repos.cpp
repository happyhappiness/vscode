static struct push_cas *add_cas_entry(struct push_cas_option *cas,
				      const char *refname,
				      size_t refnamelen)
{
	struct push_cas *entry;
	ALLOC_GROW(cas->entry, cas->nr + 1, cas->alloc);
	entry = &cas->entry[cas->nr++];
	memset(entry, 0, sizeof(*entry));
	entry->refname = xmemdupz(refname, refnamelen);
	return entry;
}