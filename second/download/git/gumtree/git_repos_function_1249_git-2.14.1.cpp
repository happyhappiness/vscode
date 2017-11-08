int handle_revision_arg(const char *arg_, struct rev_info *revs, int flags, unsigned revarg_opt)
{
	struct object_context oc;
	char *mark;
	struct object *object;
	struct object_id oid;
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

	if (get_sha1_with_context(arg, get_sha1_flags, oid.hash, &oc))
		return revs->ignore_missing ? 0 : -1;
	if (!cant_be_filename)
		verify_non_filename(revs->prefix, arg);
	object = get_reference(revs, arg, &oid, flags ^ local_flags);
	add_rev_cmdline(revs, object, arg_, REV_CMD_REV, flags ^ local_flags);
	add_pending_object_with_path(revs, object, arg, oc.mode, oc.path);
	free(oc.path);
	return 0;
}