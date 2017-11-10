static const char *resolve_ref_1(const char *refname,
				 int resolve_flags,
				 unsigned char *sha1,
				 int *flags,
				 struct strbuf *sb_refname,
				 struct strbuf *sb_path,
				 struct strbuf *sb_contents)
{
	int depth = MAXDEPTH;
	int bad_name = 0;

	if (flags)
		*flags = 0;

	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
		if (flags)
			*flags |= REF_BAD_NAME;

		if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
		    !refname_is_safe(refname)) {
			errno = EINVAL;
			return NULL;
		}
		/*
		 * dwim_ref() uses REF_ISBROKEN to distinguish between
		 * missing refs and refs that were present but invalid,
		 * to complain about the latter to stderr.
		 *
		 * We don't know whether the ref exists, so don't set
		 * REF_ISBROKEN yet.
		 */
		bad_name = 1;
	}
	for (;;) {
		const char *path;
		struct stat st;
		char *buf;
		int fd;

		if (--depth < 0) {
			errno = ELOOP;
			return NULL;
		}

		strbuf_reset(sb_path);
		strbuf_git_path(sb_path, "%s", refname);
		path = sb_path->buf;

		/*
		 * We might have to loop back here to avoid a race
		 * condition: first we lstat() the file, then we try
		 * to read it as a link or as a file.  But if somebody
		 * changes the type of the file (file <-> directory
		 * <-> symlink) between the lstat() and reading, then
		 * we don't want to report that as an error but rather
		 * try again starting with the lstat().
		 */
	stat_ref:
		if (lstat(path, &st) < 0) {
			if (errno != ENOENT)
				return NULL;
			if (resolve_missing_loose_ref(refname, resolve_flags,
						      sha1, flags))
				return NULL;
			if (bad_name) {
				hashclr(sha1);
				if (flags)
					*flags |= REF_ISBROKEN;
			}
			return refname;
		}

		/* Follow "normalized" - ie "refs/.." symlinks by hand */
		if (S_ISLNK(st.st_mode)) {
			strbuf_reset(sb_contents);
			if (strbuf_readlink(sb_contents, path, 0) < 0) {
				if (errno == ENOENT || errno == EINVAL)
					/* inconsistent with lstat; retry */
					goto stat_ref;
				else
					return NULL;
			}
			if (starts_with(sb_contents->buf, "refs/") &&
			    !check_refname_format(sb_contents->buf, 0)) {
				strbuf_swap(sb_refname, sb_contents);
				refname = sb_refname->buf;
				if (flags)
					*flags |= REF_ISSYMREF;
				if (resolve_flags & RESOLVE_REF_NO_RECURSE) {
					hashclr(sha1);
					return refname;
				}
				continue;
			}
		}

		/* Is it a directory? */
		if (S_ISDIR(st.st_mode)) {
			errno = EISDIR;
			return NULL;
		}

		/*
		 * Anything else, just open it and try to use it as
		 * a ref
		 */
		fd = open(path, O_RDONLY);
		if (fd < 0) {
			if (errno == ENOENT)
				/* inconsistent with lstat; retry */
				goto stat_ref;
			else
				return NULL;
		}
		strbuf_reset(sb_contents);
		if (strbuf_read(sb_contents, fd, 256) < 0) {
			int save_errno = errno;
			close(fd);
			errno = save_errno;
			return NULL;
		}
		close(fd);
		strbuf_rtrim(sb_contents);

		/*
		 * Is it a symbolic ref?
		 */
		if (!starts_with(sb_contents->buf, "ref:")) {
			/*
			 * Please note that FETCH_HEAD has a second
			 * line containing other data.
			 */
			if (get_sha1_hex(sb_contents->buf, sha1) ||
			    (sb_contents->buf[40] != '\0' && !isspace(sb_contents->buf[40]))) {
				if (flags)
					*flags |= REF_ISBROKEN;
				errno = EINVAL;
				return NULL;
			}
			if (bad_name) {
				hashclr(sha1);
				if (flags)
					*flags |= REF_ISBROKEN;
			}
			return refname;
		}
		if (flags)
			*flags |= REF_ISSYMREF;
		buf = sb_contents->buf + 4;
		while (isspace(*buf))
			buf++;
		strbuf_reset(sb_refname);
		strbuf_addstr(sb_refname, buf);
		refname = sb_refname->buf;
		if (resolve_flags & RESOLVE_REF_NO_RECURSE) {
			hashclr(sha1);
			return refname;
		}
		if (check_refname_format(buf, REFNAME_ALLOW_ONELEVEL)) {
			if (flags)
				*flags |= REF_ISBROKEN;

			if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
			    !refname_is_safe(buf)) {
				errno = EINVAL;
				return NULL;
			}
			bad_name = 1;
		}
	}
}