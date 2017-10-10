		xsnprintf(temp->mode, sizeof(temp->mode), ".");
		return temp;
	}

	if (!S_ISGITLINK(one->mode) &&
	    (!one->oid_valid ||
	     reuse_worktree_file(name, &one->oid, 1))) {
		struct stat st;
		if (lstat(name, &st) < 0) {
			if (errno == ENOENT)
				goto not_a_valid_file;
			die_errno("stat(%s)", name);
		}
