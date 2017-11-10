static int for_each_replace_name(const char **argv, each_replace_name_fn fn)
{
	const char **p, *full_hex;
	char ref[PATH_MAX];
	int had_error = 0;
	unsigned char sha1[20];

	for (p = argv; *p; p++) {
		if (get_sha1(*p, sha1)) {
			error("Failed to resolve '%s' as a valid ref.", *p);
			had_error = 1;
			continue;
		}
		full_hex = sha1_to_hex(sha1);
		snprintf(ref, sizeof(ref), "%s%s", git_replace_ref_base, full_hex);
		/* read_ref() may reuse the buffer */
		full_hex = ref + strlen(git_replace_ref_base);
		if (read_ref(ref, sha1)) {
			error("replace ref '%s' not found.", full_hex);
			had_error = 1;
			continue;
		}
		if (fn(full_hex, ref, sha1))
			had_error = 1;
	}
	return had_error;
}