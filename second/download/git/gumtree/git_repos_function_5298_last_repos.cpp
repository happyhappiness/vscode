static int try_parent_shorthands(const char *arg)
{
	char *dotdot;
	struct object_id oid;
	struct commit *commit;
	struct commit_list *parents;
	int parent_number;
	int include_rev = 0;
	int include_parents = 0;
	int exclude_parent = 0;

	if ((dotdot = strstr(arg, "^!"))) {
		include_rev = 1;
		if (dotdot[2])
			return 0;
	} else if ((dotdot = strstr(arg, "^@"))) {
		include_parents = 1;
		if (dotdot[2])
			return 0;
	} else if ((dotdot = strstr(arg, "^-"))) {
		include_rev = 1;
		exclude_parent = 1;

		if (dotdot[2]) {
			char *end;
			exclude_parent = strtoul(dotdot + 2, &end, 10);
			if (*end != '\0' || !exclude_parent)
				return 0;
		}
	} else
		return 0;

	*dotdot = 0;
	if (get_sha1_committish(arg, oid.hash)) {
		*dotdot = '^';
		return 0;
	}

	commit = lookup_commit_reference(&oid);
	if (exclude_parent &&
	    exclude_parent > commit_list_count(commit->parents)) {
		*dotdot = '^';
		return 0;
	}

	if (include_rev)
		show_rev(NORMAL, &oid, arg);
	for (parents = commit->parents, parent_number = 1;
	     parents;
	     parents = parents->next, parent_number++) {
		char *name = NULL;

		if (exclude_parent && parent_number != exclude_parent)
			continue;

		if (symbolic)
			name = xstrfmt("%s^%d", arg, parent_number);
		show_rev(include_parents ? NORMAL : REVERSED,
			 &parents->item->object.oid, name);
		free(name);
	}

	*dotdot = '^';
	return 1;
}