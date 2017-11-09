struct file_struct *make_file(const char *fname, struct file_list *flist,
			      STRUCT_STAT *stp, int flags, int filter_level)
{
	static char *lastdir;
	static int lastdir_len = -1;
	struct file_struct *file;
	char thisname[MAXPATHLEN];
	char linkname[MAXPATHLEN];
	int alloc_len, basename_len, linkname_len;
	int extra_len = file_extra_cnt * EXTRA_LEN;
	const char *basename;
	alloc_pool_t *pool;
	STRUCT_STAT st;
	char *bp;

	if (strlcpy(thisname, fname, sizeof thisname) >= sizeof thisname) {
		io_error |= IOERR_GENERAL;
		rprintf(FERROR_XFER, "skipping overly long name: %s\n", fname);
		return NULL;
	}
	clean_fname(thisname, 0);
	if (sanitize_paths)
		sanitize_path(thisname, thisname, "", 0, SP_DEFAULT);

	if (stp && (S_ISDIR(stp->st_mode) || IS_MISSING_FILE(*stp))) {
		/* This is needed to handle a "symlink/." with a --relative
		 * dir, or a request to delete a specific file. */
		st = *stp;
		*linkname = '\0'; /* make IBM code checker happy */
	} else if (readlink_stat(thisname, &st, linkname) != 0) {
		int save_errno = errno;
		/* See if file is excluded before reporting an error. */
		if (filter_level != NO_FILTERS
		 && (is_excluded(thisname, 0, filter_level)
		  || is_excluded(thisname, 1, filter_level))) {
			if (ignore_perishable && save_errno != ENOENT)
				non_perishable_cnt++;
			return NULL;
		}
		if (save_errno == ENOENT) {
#ifdef SUPPORT_LINKS
			/* When our options tell us to follow a symlink that
			 * points nowhere, tell the user about the symlink
			 * instead of giving a "vanished" message.  We only
			 * dereference a symlink if one of the --copy*links
			 * options was specified, so there's no need for the
			 * extra lstat() if one of these options isn't on. */
			if ((copy_links || copy_unsafe_links || copy_dirlinks)
			 && x_lstat(thisname, &st, NULL) == 0
			 && S_ISLNK(st.st_mode)) {
				io_error |= IOERR_GENERAL;
				rprintf(FERROR_XFER, "symlink has no referent: %s\n",
					full_fname(thisname));
			} else
#endif
			{
				enum logcode c = am_daemon && protocol_version < 28
					       ? FERROR : FWARNING;
				io_error |= IOERR_VANISHED;
				rprintf(c, "file has vanished: %s\n",
					full_fname(thisname));
			}
		} else {
			io_error |= IOERR_GENERAL;
			rsyserr(FERROR_XFER, save_errno, "readlink_stat(%s) failed",
				full_fname(thisname));
		}
		return NULL;
	} else if (IS_MISSING_FILE(st)) {
		io_error |= IOERR_GENERAL;
		rprintf(FINFO, "skipping file with bogus (zero) st_mode: %s\n",
			full_fname(thisname));
		return NULL;
	}

	if (filter_level == NO_FILTERS)
		goto skip_filters;

	if (S_ISDIR(st.st_mode)) {
		if (!xfer_dirs) {
			rprintf(FINFO, "skipping directory %s\n", thisname);
			return NULL;
		}
		/* -x only affects dirs because we need to avoid recursing
		 * into a mount-point directory, not to avoid copying a
		 * symlinked file if -L (or similar) was specified. */
		if (one_file_system && st.st_dev != filesystem_dev
		 && BITS_SETnUNSET(flags, FLAG_CONTENT_DIR, FLAG_TOP_DIR)) {
			if (one_file_system > 1) {
				if (INFO_GTE(MOUNT, 1)) {
					rprintf(FINFO,
					    "[%s] skipping mount-point dir %s\n",
					    who_am_i(), thisname);
				}
				return NULL;
			}
			flags |= FLAG_MOUNT_DIR;
			flags &= ~FLAG_CONTENT_DIR;
		}
	} else
		flags &= ~FLAG_CONTENT_DIR;

	if (is_excluded(thisname, S_ISDIR(st.st_mode) != 0, filter_level)) {
		if (ignore_perishable)
			non_perishable_cnt++;
		return NULL;
	}

	if (lp_ignore_nonreadable(module_id)) {
#ifdef SUPPORT_LINKS
		if (!S_ISLNK(st.st_mode))
#endif
			if (access(thisname, R_OK) != 0)
				return NULL;
	}

  skip_filters:

	/* Only divert a directory in the main transfer. */
	if (flist) {
		if (flist->prev && S_ISDIR(st.st_mode)
		 && flags & FLAG_DIVERT_DIRS) {
			/* Room for parent/sibling/next-child info. */
			extra_len += DIRNODE_EXTRA_CNT * EXTRA_LEN;
			if (relative_paths)
				extra_len += PTR_EXTRA_CNT * EXTRA_LEN;
			pool = dir_flist->file_pool;
		} else
			pool = flist->file_pool;
	} else {
#ifdef SUPPORT_ACLS
		/* Directories need an extra int32 for the default ACL. */
		if (preserve_acls && S_ISDIR(st.st_mode))
			extra_len += EXTRA_LEN;
#endif
		pool = NULL;
	}

	if (DEBUG_GTE(FLIST, 2)) {
		rprintf(FINFO, "[%s] make_file(%s,*,%d)\n",
			who_am_i(), thisname, filter_level);
	}

	if ((basename = strrchr(thisname, '/')) != NULL) {
		int len = basename++ - thisname;
		if (len != lastdir_len || memcmp(thisname, lastdir, len) != 0) {
			lastdir = new_array(char, len + 1);
			memcpy(lastdir, thisname, len);
			lastdir[len] = '\0';
			lastdir_len = len;
		}
	} else
		basename = thisname;
	basename_len = strlen(basename) + 1; /* count the '\0' */

#ifdef SUPPORT_LINKS
	linkname_len = S_ISLNK(st.st_mode) ? strlen(linkname) + 1 : 0;
#else
	linkname_len = 0;
#endif

#ifdef ST_MTIME_NSEC
	if (st.ST_MTIME_NSEC && protocol_version >= 31)
		extra_len += EXTRA_LEN;
#endif
#if SIZEOF_CAPITAL_OFF_T >= 8
	if (st.st_size > 0xFFFFFFFFu && S_ISREG(st.st_mode))
		extra_len += EXTRA_LEN;
#endif

	if (always_checksum && am_sender && S_ISREG(st.st_mode)) {
		file_checksum(thisname, &st, tmp_sum);
		if (sender_keeps_checksum)
			extra_len += SUM_EXTRA_CNT * EXTRA_LEN;
	}

#if EXTRA_ROUNDING > 0
	if (extra_len & (EXTRA_ROUNDING * EXTRA_LEN))
		extra_len = (extra_len | (EXTRA_ROUNDING * EXTRA_LEN)) + EXTRA_LEN;
#endif

	alloc_len = FILE_STRUCT_LEN + extra_len + basename_len
		  + linkname_len;
	if (pool)
		bp = pool_alloc(pool, alloc_len, "make_file");
	else {
		if (!(bp = new_array(char, alloc_len)))
			out_of_memory("make_file");
	}

	memset(bp, 0, extra_len + FILE_STRUCT_LEN);
	bp += extra_len;
	file = (struct file_struct *)bp;
	bp += FILE_STRUCT_LEN;

	memcpy(bp, basename, basename_len);

#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && flist && flist->prev) {
		if (protocol_version >= 28
		 ? (!S_ISDIR(st.st_mode) && st.st_nlink > 1)
		 : S_ISREG(st.st_mode)) {
			tmp_dev = (int64)st.st_dev;
			tmp_ino = (int64)st.st_ino;
		} else
			tmp_dev = -1;
	}
#endif

#ifdef HAVE_STRUCT_STAT_ST_RDEV
	if (IS_DEVICE(st.st_mode)) {
		tmp_rdev = st.st_rdev;
		st.st_size = 0;
	} else if (IS_SPECIAL(st.st_mode))
		st.st_size = 0;
#endif

	file->flags = flags;
	file->modtime = st.st_mtime;
#ifdef ST_MTIME_NSEC
	if (st.ST_MTIME_NSEC && protocol_version >= 31) {
		file->flags |= FLAG_MOD_NSEC;
		OPT_EXTRA(file, 0)->unum = st.ST_MTIME_NSEC;
	}
#endif
	file->len32 = (uint32)st.st_size;
#if SIZEOF_CAPITAL_OFF_T >= 8
	if (st.st_size > 0xFFFFFFFFu && S_ISREG(st.st_mode)) {
		file->flags |= FLAG_LENGTH64;
		OPT_EXTRA(file, NSEC_BUMP(file))->unum = (uint32)(st.st_size >> 32);
	}
#endif
	file->mode = st.st_mode;
	if (preserve_uid)
		F_OWNER(file) = st.st_uid;
	if (preserve_gid)
		F_GROUP(file) = st.st_gid;
	if (am_generator && st.st_uid == our_uid)
		file->flags |= FLAG_OWNED_BY_US;

	if (basename != thisname)
		file->dirname = lastdir;

#ifdef SUPPORT_LINKS
	if (linkname_len)
		memcpy(bp + basename_len, linkname, linkname_len);
#endif

	if (am_sender)
		F_PATHNAME(file) = pathname;
	else if (!pool)
		F_DEPTH(file) = extra_len / EXTRA_LEN;

	if (basename_len == 0+1) {
		if (!pool)
			unmake_file(file);
		return NULL;
	}

	if (sender_keeps_checksum && S_ISREG(st.st_mode))
		memcpy(F_SUM(file), tmp_sum, checksum_len);

	if (unsort_ndx)
		F_NDX(file) = stats.num_dirs;

	return file;
}