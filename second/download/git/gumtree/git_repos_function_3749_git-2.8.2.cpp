static const struct ref *find_ref_by_name_abbrev(const struct ref *refs, const char *name)
{
	const struct ref *ref;
	for (ref = refs; ref; ref = ref->next) {
		if (refname_match(name, ref->name))
			return ref;
	}
	return NULL;
}