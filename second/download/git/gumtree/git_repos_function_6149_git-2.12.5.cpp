static int files_read_raw_ref(struct ref_store *ref_store,
			      const char *refname, unsigned char *sha1,
			      struct strbuf *referent, unsigned int *type)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, 1, "read_raw_ref");
	struct strbuf sb_contents = STRBUF_INIT;
	struct strbuf sb_path = STRBUF_INIT;
	const char *path;
	const char *buf;
	struct stat st;
	int fd;
	int ret = -1;
	int save_errno;
	int remaining_retries = 3;

	*type = 0;
	strbuf_reset(&sb_path);

	if (*refs->base.submodule)
		strbuf_git_path_submodule(&sb_path, refs->base.submodule, "%s", refname);
	else
		strbuf_git_path(&sb_path, "%s", refname);

	path = sb_path.buf;

stat_ref:
	/*
	 * We might have to loop back here to avoid a race
	 * condition: first we lstat() the file, then we try
	 * to read it as a link or as a file.  But if somebody
	 * changes the type of the file (file <-> directory
	 * <-> symlink) between the lstat() and reading, then
	 * we don't want to report that as an error but rather
	 * try again starting with the lstat().
	 *
	 * We'll keep a count of the retries, though, just to avoid
	 * any confusing situation sending us into an infinite loop.
	 */

	if (remaining_retries-- <= 0)
		goto out;

	if (lstat(path, &st) < 0) {
		if (errno != ENOENT)
			goto out;
		if (resolve_packed_ref(refs, refname, sha1, type)) {
			errno = ENOENT;
			goto out;
		}
		ret = 0;
		goto out;
	}

	/* Follow "normalized" - ie "refs/.." symlinks by hand */
	if (S_ISLNK(st.st_mode)) {
		strbuf_reset(&sb_contents);
		if (strbuf_readlink(&sb_contents, path, 0) < 0) {
			if (errno == ENOENT || errno == EINVAL)
				/* inconsistent with lstat; retry */
				goto stat_ref;
			else
				goto out;
		}
		if (starts_with(sb_contents.buf, "refs/") &&
		    !check_refname_format(sb_contents.buf, 0)) {
			strbuf_swap(&sb_contents, referent);
			*type |= REF_ISSYMREF;
			ret = 0;
			goto out;
		}
		/*
		 * It doesn't look like a refname; fall through to just
		 * treating it like a non-symlink, and reading whatever it
		 * points to.
		 */
	}

	/* Is it a directory? */
	if (S_ISDIR(st.st_mode)) {
		/*
		 * Even though there is a directory where the loose
		 * ref is supposed to be, there could still be a
		 * packed ref:
		 */
		if (resolve_packed_ref(refs, refname, sha1, type)) {
			errno = EISDIR;
			goto out;
		}
		ret = 0;
		goto out;
	}

	/*
	 * Anything else, just open it and try to use it as
	 * a ref
	 */
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		if (errno == ENOENT && !S_ISLNK(st.st_mode))
			/* inconsistent with lstat; retry */
			goto stat_ref;
		else
			goto out;
	}
	strbuf_reset(&sb_contents);
	if (strbuf_read(&sb_contents, fd, 256) < 0) {
		int save_errno = errno;
		close(fd);
		errno = save_errno;
		goto out;
	}
	close(fd);
	strbuf_rtrim(&sb_contents);
	buf = sb_contents.buf;
	if (starts_with(buf, "ref:")) {
		buf += 4;
		while (isspace(*buf))
			buf++;

		strbuf_reset(referent);
		strbuf_addstr(referent, buf);
		*type |= REF_ISSYMREF;
		ret = 0;
		goto out;
	}

	/*
	 * Please note that FETCH_HEAD has additional
	 * data after the sha.
	 */
	if (get_sha1_hex(buf, sha1) ||
	    (buf[40] != '\0' && !isspace(buf[40]))) {
		*type |= REF_ISBROKEN;
		errno = EINVAL;
		goto out;
	}

	ret = 0;

out:
	save_errno = errno;
	strbuf_release(&sb_path);
	strbuf_release(&sb_contents);
	errno = save_errno;
	return ret;
}