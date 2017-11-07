static void write_followtags(const struct ref *refs, const char *msg)
{
	const struct ref *ref;
	for (ref = refs; ref; ref = ref->next) {
		if (!starts_with(ref->name, "refs/tags/"))
			continue;
		if (ends_with(ref->name, "^{}"))
			continue;
		if (!has_object_file(&ref->old_oid))
			continue;
		update_ref(msg, ref->name, ref->old_oid.hash,
			   NULL, 0, UPDATE_REFS_DIE_ON_ERR);
	}
}