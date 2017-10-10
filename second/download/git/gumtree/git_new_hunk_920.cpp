	N_("git merge-base --fork-point <ref> [<commit>]"),
	NULL
};

static struct commit *get_commit_reference(const char *arg)
{
	struct object_id revkey;
	struct commit *r;

	if (get_oid(arg, &revkey))
		die("Not a valid object name %s", arg);
	r = lookup_commit_reference(revkey.hash);
	if (!r)
		die("Not a valid commit name %s", arg);

	return r;
}

