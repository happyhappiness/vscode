static int register_ref(const char *refname, const unsigned char *sha1,
			int flags, void *cb_data)
{
	if (!strcmp(refname, "bad")) {
		current_bad_sha1 = xmalloc(20);
		hashcpy(current_bad_sha1, sha1);
	} else if (starts_with(refname, "good-")) {
		sha1_array_append(&good_revs, sha1);
	} else if (starts_with(refname, "skip-")) {
		sha1_array_append(&skipped_revs, sha1);
	}

	return 0;
}