static int update_local_ref(const char *name,
			    const char *new_head,
			    const char *note,
			    int verbose, int force)
{
	unsigned char sha1_old[20], sha1_new[20];
	char oldh[41], newh[41];
	struct commit *current, *updated;
	enum object_type type;

	if (get_sha1_hex(new_head, sha1_new))
		die("malformed object name %s", new_head);

	type = sha1_object_info(sha1_new, NULL);
	if (type < 0)
		die("object %s not found", new_head);

	if (!*name) {
		/* Not storing */
		if (verbose) {
			fprintf(stderr, "* fetched %s\n", note);
			show_new(type, sha1_new);
		}
		return 0;
	}

	if (get_sha1(name, sha1_old)) {
		const char *msg;
	just_store:
		/* new ref */
		if (!strncmp(name, "refs/tags/", 10))
			msg = "storing tag";
		else
			msg = "storing head";
		fprintf(stderr, "* %s: storing %s\n",
			name, note);
		show_new(type, sha1_new);
		return update_ref_env(msg, name, sha1_new, NULL);
	}

	if (!hashcmp(sha1_old, sha1_new)) {
		if (verbose) {
			fprintf(stderr, "* %s: same as %s\n", name, note);
			show_new(type, sha1_new);
		}
		return 0;
	}

	if (!strncmp(name, "refs/tags/", 10)) {
		fprintf(stderr, "* %s: updating with %s\n", name, note);
		show_new(type, sha1_new);
		return update_ref_env("updating tag", name, sha1_new, NULL);
	}

	current = lookup_commit_reference(sha1_old);
	updated = lookup_commit_reference(sha1_new);
	if (!current || !updated)
		goto just_store;

	strcpy(oldh, find_unique_abbrev(current->object.sha1, DEFAULT_ABBREV));
	strcpy(newh, find_unique_abbrev(sha1_new, DEFAULT_ABBREV));

	if (in_merge_bases(current, updated)) {
		fprintf(stderr, "* %s: fast-forward to %s\n",
			name, note);
		fprintf(stderr, "  old..new: %s..%s\n", oldh, newh);
		return update_ref_env("fast-forward", name, sha1_new, sha1_old);
	}
	if (!force) {
		fprintf(stderr,
			"* %s: not updating to non-fast-forward %s\n",
			name, note);
		fprintf(stderr,
			"  old...new: %s...%s\n", oldh, newh);
		return 1;
	}
	fprintf(stderr,
		"* %s: forcing update to non-fast-forward %s\n",
		name, note);
	fprintf(stderr, "  old...new: %s...%s\n", oldh, newh);
	return update_ref_env("forced-update", name, sha1_new, sha1_old);
}