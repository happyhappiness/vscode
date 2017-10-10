	clear_pathspec(&revs->prune_data);
	parse_pathspec(&revs->prune_data, PATHSPEC_ALL_MAGIC & ~PATHSPEC_LITERAL,
		       PATHSPEC_PREFER_FULL | PATHSPEC_LITERAL_PATH, "", prune);
	revs->limited = 1;
}

static int dotdot_missing(const char *arg, char *dotdot,
			  struct rev_info *revs, int symmetric)
{
	if (revs->ignore_missing)
		return 0;
	/* de-munge so we report the full argument */
	*dotdot = '.';
	die(symmetric
	    ? "Invalid symmetric difference expression %s"
	    : "Invalid revision range %s", arg);
}

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

	a_obj = parse_object(a_oid.hash);
	b_obj = parse_object(b_oid.hash);
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

		a = lookup_commit_reference(a_obj->oid.hash);
		b = lookup_commit_reference(b_obj->oid.hash);
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

static int handle_dotdot(const char *arg,
			 struct rev_info *revs, int flags,
			 int cant_be_filename)
{
	struct object_context a_oc, b_oc;
	char *dotdot = strstr(arg, "..");
	int ret;

	if (!dotdot)
		return -1;

	memset(&a_oc, 0, sizeof(a_oc));
	memset(&b_oc, 0, sizeof(b_oc));

	*dotdot = '\0';
	ret = handle_dotdot_1(arg, dotdot, revs, flags, cant_be_filename,
			      &a_oc, &b_oc);
	*dotdot = '.';

	free(a_oc.path);
	free(b_oc.path);

	return ret;
}

int handle_revision_arg(const char *arg_, struct rev_info *revs, int flags, unsigned revarg_opt)
{
	struct object_context oc;
	char *mark;
	struct object *object;
	unsigned char sha1[20];
	int local_flags;
	const char *arg = arg_;
	int cant_be_filename = revarg_opt & REVARG_CANNOT_BE_FILENAME;
	unsigned get_sha1_flags = GET_SHA1_RECORD_PATH;

	flags = flags & UNINTERESTING ? flags | BOTTOM : flags & ~BOTTOM;

	if (!cant_be_filename && !strcmp(arg, "..")) {
		/*
		 * Just ".."?  That is not a range but the
		 * pathspec for the parent directory.
		 */
		return -1;
	}

	if (!handle_dotdot(arg, revs, flags, revarg_opt))
		return 0;

	mark = strstr(arg, "^@");
	if (mark && !mark[2]) {
		*mark = 0;
		if (add_parents_only(revs, arg, flags, 0))
			return 0;
		*mark = '^';
	}
	mark = strstr(arg, "^!");
	if (mark && !mark[2]) {
		*mark = 0;
		if (!add_parents_only(revs, arg, flags ^ (UNINTERESTING | BOTTOM), 0))
			*mark = '^';
	}
	mark = strstr(arg, "^-");
	if (mark) {
		int exclude_parent = 1;

		if (mark[2]) {
			char *end;
			exclude_parent = strtoul(mark + 2, &end, 10);
			if (*end != '\0' || !exclude_parent)
				return -1;
		}

		*mark = 0;
		if (!add_parents_only(revs, arg, flags ^ (UNINTERESTING | BOTTOM), exclude_parent))
			*mark = '^';
	}

	local_flags = 0;
	if (*arg == '^') {
		local_flags = UNINTERESTING | BOTTOM;
		arg++;
	}

	if (revarg_opt & REVARG_COMMITTISH)
		get_sha1_flags |= GET_SHA1_COMMITTISH;

	if (get_sha1_with_context(arg, get_sha1_flags, sha1, &oc))
		return revs->ignore_missing ? 0 : -1;
	if (!cant_be_filename)
		verify_non_filename(revs->prefix, arg);
	object = get_reference(revs, arg, sha1, flags ^ local_flags);
	add_rev_cmdline(revs, object, arg_, REV_CMD_REV, flags ^ local_flags);
	add_pending_object_with_path(revs, object, arg, oc.mode, oc.path);
	free(oc.path);
	return 0;
}

struct cmdline_pathspec {
	int alloc;
	int nr;
