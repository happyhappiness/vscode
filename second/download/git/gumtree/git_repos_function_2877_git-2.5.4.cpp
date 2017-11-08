static int register_ref(const char *refname, const struct object_id *oid,
			int flags, void *cb_data)
{
	if (!strcmp(refname, "bad")) {
		current_bad_oid = xmalloc(sizeof(*current_bad_oid));
		oidcpy(current_bad_oid, oid);
	} else if (starts_with(refname, "good-")) {
		sha1_array_append(&good_revs, oid->hash);
	} else if (starts_with(refname, "skip-")) {
		sha1_array_append(&skipped_revs, oid->hash);
	}

	return 0;
}