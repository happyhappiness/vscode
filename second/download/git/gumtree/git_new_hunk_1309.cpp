{
	struct object_id revkey;
	struct commit *r;

	if (get_oid(arg, &revkey))
		die("Not a valid object name %s", arg);
	r = lookup_commit_reference(&revkey);
	if (!r)
		die("Not a valid commit name %s", arg);

	return r;
}

