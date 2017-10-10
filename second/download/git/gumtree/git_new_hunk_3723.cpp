		xsnprintf(temp->hex, sizeof(temp->hex), ".");
		xsnprintf(temp->mode, sizeof(temp->mode), ".");
		return temp;
	}

	if (!S_ISGITLINK(one->mode) &&
	    (!one->oid_valid ||
	     reuse_worktree_file(name, one->oid.hash, 1))) {
		struct stat st;
		if (lstat(name, &st) < 0) {
			if (errno == ENOENT)
				goto not_a_valid_file;
			die_errno("stat(%s)", name);
		}
		if (S_ISLNK(st.st_mode)) {
			struct strbuf sb = STRBUF_INIT;
			if (strbuf_readlink(&sb, name, st.st_size) < 0)
				die_errno("readlink(%s)", name);
			prep_temp_blob(name, temp, sb.buf, sb.len,
				       (one->oid_valid ?
					&one->oid : &null_oid),
				       (one->oid_valid ?
					one->mode : S_IFLNK));
			strbuf_release(&sb);
		}
		else {
			/* we can borrow from the file in the work tree */
			temp->name = name;
			if (!one->oid_valid)
				sha1_to_hex_r(temp->hex, null_sha1);
			else
				sha1_to_hex_r(temp->hex, one->oid.hash);
			/* Even though we may sometimes borrow the
			 * contents from the work tree, we always want
			 * one->mode.  mode is trustworthy even when
			 * !(one->sha1_valid), as long as
			 * DIFF_FILE_VALID(one).
			 */
