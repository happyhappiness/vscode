 * stat()ing the file in some circumstances, which has a certain cost.
 * We are called immediately after doing readdir(), and so we may
 * already know the d_type of the file.  We could for example avoid
 * statting directories if we're not recursing, but this is not a very
 * important case.  Some systems may not have d_type.
 **/
struct file_struct *make_file(char *fname,
    struct file_list *flist, int exclude_level)
{
	static char *lastdir;
	static int lastdir_len = -1;
	struct file_struct *file;
	STRUCT_STAT st;
	char sum[SUM_LENGTH];
	char thisname[MAXPATHLEN];
	char linkname[MAXPATHLEN];
	int alloc_len, basename_len, dirname_len, linkname_len, sum_len;
	char *basename, *dirname, *bp;
	unsigned short flags = 0;

	if (!flist)	/* lastdir isn't valid if flist is NULL */
		lastdir_len = -1;

	if (strlcpy(thisname, fname, sizeof thisname)
	    >= sizeof thisname - flist_dir_len) {
		rprintf(FINFO, "skipping overly long name: %s\n", fname);
		return NULL;
	}
	clean_fname(thisname);
	if (sanitize_paths)
		sanitize_path(thisname, NULL);

	memset(sum, 0, SUM_LENGTH);

	if (readlink_stat(thisname, &st, linkname) != 0) {
		int save_errno = errno;
		if (errno == ENOENT) {
			enum logcode c = am_daemon && protocol_version < 28
			    ? FERROR : FINFO;
			/* either symlink pointing nowhere or file that
			 * was removed during rsync run; see if excluded
			 * before reporting an error */
			if (exclude_level != NO_EXCLUDES
			    && check_exclude_file(thisname, 0, exclude_level)) {
				/* file is excluded anyway, ignore silently */
				return NULL;
			}
			io_error |= IOERR_VANISHED;
			rprintf(c, "file has vanished: %s\n",
			    full_fname(thisname));
		}
		else {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR, "readlink %s failed: %s\n",
			    full_fname(thisname), strerror(save_errno));
		}
		return NULL;
	}

	/* backup.c calls us with exclude_level set to NO_EXCLUDES. */
	if (exclude_level == NO_EXCLUDES)
		goto skip_excludes;

	if (S_ISDIR(st.st_mode) && !recurse && !files_from) {
		rprintf(FINFO, "skipping directory %s\n", thisname);
		return NULL;
	}

	/* We only care about directories because we need to avoid recursing
	 * into a mount-point directory, not to avoid copying a symlinked
	 * file if -L (or similar) was specified. */
	if (one_file_system && st.st_dev != filesystem_dev
	    && S_ISDIR(st.st_mode))
		flags |= FLAG_MOUNT_POINT;

	if (check_exclude_file(thisname, S_ISDIR(st.st_mode) != 0, exclude_level))
		return NULL;

	if (lp_ignore_nonreadable(module_id) && access(thisname, R_OK) != 0)
		return NULL;

skip_excludes:

	if (verbose > 2) {
		rprintf(FINFO, "[%s] make_file(%s,*,%d)\n",
			who_am_i(), thisname, exclude_level);
	}

	if ((basename = strrchr(thisname, '/')) != NULL) {
		dirname_len = ++basename - thisname; /* counts future '\0' */
		if (lastdir_len == dirname_len - 1
		    && strncmp(thisname, lastdir, lastdir_len) == 0) {
			dirname = lastdir;
			dirname_len = 0; /* indicates no copy is needed */
		} else
			dirname = thisname;
	} else {
		basename = thisname;
		dirname = NULL;
		dirname_len = 0;
	}
	basename_len = strlen(basename) + 1; /* count the '\0' */

#if SUPPORT_LINKS
	linkname_len = S_ISLNK(st.st_mode) ? strlen(linkname) + 1 : 0;
#else
	linkname_len = 0;
#endif

	sum_len = always_checksum && S_ISREG(st.st_mode) ? MD4_SUM_LENGTH : 0;

	alloc_len = file_struct_len + dirname_len + basename_len
	    + linkname_len + sum_len;
	if (flist) {
		bp = pool_alloc(flist->file_pool, alloc_len,
		    "receive_file_entry");
	} else {
		if (!(bp = new_array(char, alloc_len)))
			out_of_memory("receive_file_entry");
	}

	file = (struct file_struct *)bp;
	memset(bp, 0, file_struct_len);
	bp += file_struct_len;

	file->flags = flags;
	file->modtime = st.st_mtime;
	file->length = st.st_size;
	file->mode = st.st_mode;
	file->uid = st.st_uid;
	file->gid = st.st_gid;

#if SUPPORT_HARD_LINKS
	if (flist && flist->hlink_pool) {
		if (protocol_version < 28) {
			if (S_ISREG(st.st_mode))
				file->link_u.idev = pool_talloc(
				    flist->hlink_pool, struct idev, 1,
				    "inode_table");
		} else {
			if (!S_ISDIR(st.st_mode) && st.st_nlink > 1)
				file->link_u.idev = pool_talloc(
				    flist->hlink_pool, struct idev, 1,
				    "inode_table");
		}
	}
	if (file->link_u.idev) {
		file->F_DEV = st.st_dev;
		file->F_INODE = st.st_ino;
	}
#endif

	if (dirname_len) {
		file->dirname = lastdir = bp;
		lastdir_len = dirname_len - 1;
		memcpy(bp, dirname, dirname_len - 1);
		bp += dirname_len;
		bp[-1] = '\0';
	} else if (dirname)
		file->dirname = dirname;

	file->basename = bp;
	memcpy(bp, basename, basename_len);
	bp += basename_len;

#ifdef HAVE_STRUCT_STAT_ST_RDEV
	if (preserve_devices && IS_DEVICE(st.st_mode))
		file->u.rdev = st.st_rdev;
#endif

#if SUPPORT_LINKS
	if (linkname_len) {
		file->u.link = bp;
		memcpy(bp, linkname, linkname_len);
		bp += linkname_len;
	}
#endif

	if (sum_len) {
		file->u.sum = bp;
		file_checksum(thisname, bp, st.st_size);
		/*bp += sum_len;*/
	}

	file->basedir = flist_dir;

	if (!S_ISDIR(st.st_mode))
		stats.total_size += st.st_size;

	return file;
}
