static struct diff_tempfile *prepare_temp_file(const char *name,
		struct diff_filespec *one)
{
	struct diff_tempfile *temp = claim_diff_tempfile();

	if (!DIFF_FILE_VALID(one)) {
	not_a_valid_file:
		/* A '-' entry produces this for file-2, and
		 * a '+' entry produces this for file-1.
		 */
		temp->name = "/dev/null";
		xsnprintf(temp->hex, sizeof(temp->hex), ".");
		xsnprintf(temp->mode, sizeof(temp->mode), ".");
		return temp;
	}

	if (!S_ISGITLINK(one->mode) &&
	    (!one->sha1_valid ||
	     reuse_worktree_file(name, one->sha1, 1))) {
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
				       (one->sha1_valid ?
					one->sha1 : null_sha1),
				       (one->sha1_valid ?
					one->mode : S_IFLNK));
			strbuf_release(&sb);
		}
		else {
			/* we can borrow from the file in the work tree */
			temp->name = name;
			if (!one->sha1_valid)
				sha1_to_hex_r(temp->hex, null_sha1);
			else
				sha1_to_hex_r(temp->hex, one->sha1);
			/* Even though we may sometimes borrow the
			 * contents from the work tree, we always want
			 * one->mode.  mode is trustworthy even when
			 * !(one->sha1_valid), as long as
			 * DIFF_FILE_VALID(one).
			 */
			xsnprintf(temp->mode, sizeof(temp->mode), "%06o", one->mode);
		}
		return temp;
	}
	else {
		if (diff_populate_filespec(one, 0))
			die("cannot read data blob for %s", one->path);
		prep_temp_blob(name, temp, one->data, one->size,
			       one->sha1, one->mode);
	}
	return temp;
}