int merge_submodule(unsigned char result[20], const char *path,
		    const unsigned char base[20], const unsigned char a[20],
		    const unsigned char b[20], int search)
{
	struct commit *commit_base, *commit_a, *commit_b;
	int parent_count;
	struct object_array merges;

	int i;

	/* store a in result in case we fail */
	hashcpy(result, a);

	/* we can not handle deletion conflicts */
	if (is_null_sha1(base))
		return 0;
	if (is_null_sha1(a))
		return 0;
	if (is_null_sha1(b))
		return 0;

	if (add_submodule_odb(path)) {
		MERGE_WARNING(path, "not checked out");
		return 0;
	}

	if (!(commit_base = lookup_commit_reference(base)) ||
	    !(commit_a = lookup_commit_reference(a)) ||
	    !(commit_b = lookup_commit_reference(b))) {
		MERGE_WARNING(path, "commits not present");
		return 0;
	}

	/* check whether both changes are forward */
	if (!in_merge_bases(commit_base, commit_a) ||
	    !in_merge_bases(commit_base, commit_b)) {
		MERGE_WARNING(path, "commits don't follow merge-base");
		return 0;
	}

	/* Case #1: a is contained in b or vice versa */
	if (in_merge_bases(commit_a, commit_b)) {
		hashcpy(result, b);
		return 1;
	}
	if (in_merge_bases(commit_b, commit_a)) {
		hashcpy(result, a);
		return 1;
	}

	/*
	 * Case #2: There are one or more merges that contain a and b in
	 * the submodule. If there is only one, then present it as a
	 * suggestion to the user, but leave it marked unmerged so the
	 * user needs to confirm the resolution.
	 */

	/* Skip the search if makes no sense to the calling context.  */
	if (!search)
		return 0;

	/* find commit which merges them */
	parent_count = find_first_merges(&merges, path, commit_a, commit_b);
	switch (parent_count) {
	case 0:
		MERGE_WARNING(path, "merge following commits not found");
		break;

	case 1:
		MERGE_WARNING(path, "not fast-forward");
		fprintf(stderr, "Found a possible merge resolution "
				"for the submodule:\n");
		print_commit((struct commit *) merges.objects[0].item);
		fprintf(stderr,
			"If this is correct simply add it to the index "
			"for example\n"
			"by using:\n\n"
			"  git update-index --cacheinfo 160000 %s \"%s\"\n\n"
			"which will accept this suggestion.\n",
			sha1_to_hex(merges.objects[0].item->sha1), path);
		break;

	default:
		MERGE_WARNING(path, "multiple merges found");
		for (i = 0; i < merges.nr; i++)
			print_commit((struct commit *) merges.objects[i].item);
	}

	free(merges.objects);
	return 0;
}