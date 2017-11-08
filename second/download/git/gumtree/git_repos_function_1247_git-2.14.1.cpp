static int handle_dotdot_1(const char *arg, char *dotdot,
			   struct rev_info *revs, int flags,
			   int cant_be_filename,
			   struct object_context *a_oc,
			   struct object_context *b_oc)
{
	const char *a_name, *b_name;
	struct object_id a_oid, b_oid;
	struct object *a_obj, *b_obj;
	unsigned int a_flags, b_flags;
	int symmetric = 0;
	unsigned int flags_exclude = flags ^ (UNINTERESTING | BOTTOM);
	unsigned int oc_flags = GET_SHA1_COMMITTISH | GET_SHA1_RECORD_PATH;

	a_name = arg;
	if (!*a_name)
		a_name = "HEAD";

	b_name = dotdot + 2;
	if (*b_name == '.') {
		symmetric = 1;
		b_name++;
	}
	if (!*b_name)
		b_name = "HEAD";

	if (get_sha1_with_context(a_name, oc_flags, a_oid.hash, a_oc) ||
	    get_sha1_with_context(b_name, oc_flags, b_oid.hash, b_oc))
		return -1;

	if (!cant_be_filename) {
		*dotdot = '.';
		verify_non_filename(revs->prefix, arg);
		*dotdot = '\0';
	}

	a_obj = parse_object(&a_oid);
	b_obj = parse_object(&b_oid);
	if (!a_obj || !b_obj)
		return dotdot_missing(arg, dotdot, revs, symmetric);

	if (!symmetric) {
		/* just A..B */
		b_flags = flags;
		a_flags = flags_exclude;
	} else {
		/* A...B -- find merge bases between the two */
		struct commit *a, *b;
		struct commit_list *exclude;

		a = lookup_commit_reference(&a_obj->oid);
		b = lookup_commit_reference(&b_obj->oid);
		if (!a || !b)
			return dotdot_missing(arg, dotdot, revs, symmetric);

		exclude = get_merge_bases(a, b);
		add_rev_cmdline_list(revs, exclude, REV_CMD_MERGE_BASE,
				     flags_exclude);
		add_pending_commit_list(revs, exclude, flags_exclude);
		free_commit_list(exclude);

		b_flags = flags;
		a_flags = flags | SYMMETRIC_LEFT;
	}

	a_obj->flags |= a_flags;
	b_obj->flags |= b_flags;
	add_rev_cmdline(revs, a_obj, a_name, REV_CMD_LEFT, a_flags);
	add_rev_cmdline(revs, b_obj, b_name, REV_CMD_RIGHT, b_flags);
	add_pending_object_with_path(revs, a_obj, a_name, a_oc->mode, a_oc->path);
	add_pending_object_with_path(revs, b_obj, b_name, b_oc->mode, b_oc->path);
	return 0;
}