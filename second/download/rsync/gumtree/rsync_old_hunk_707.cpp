 * stat()ing the file in some circumstances, which has a certain cost.
 * We are called immediately after doing readdir(), and so we may
 * already know the d_type of the file.  We could for example avoid
 * statting directories if we're not recursing, but this is not a very
 * important case.  Some systems may not have d_type.
 **/
struct file_struct *make_file(char *fname, struct string_area **ap,
			      int exclude_level)
{
	struct file_struct *file;
	STRUCT_STAT st;
	char sum[SUM_LENGTH];
	char *p;
	char cleaned_name[MAXPATHLEN];
	char linkbuf[MAXPATHLEN];
	extern int module_id;

	strlcpy(cleaned_name, fname, MAXPATHLEN);
	cleaned_name[MAXPATHLEN - 1] = 0;
	clean_fname(cleaned_name);
	if (sanitize_paths) {
		sanitize_path(cleaned_name, NULL);
	}
	fname = cleaned_name;

	memset(sum, 0, SUM_LENGTH);

	if (readlink_stat(fname, &st, linkbuf) != 0) {
		int save_errno = errno;
		if (errno == ENOENT && exclude_level != NO_EXCLUDES) {
			/* either symlink pointing nowhere or file that
			 * was removed during rsync run; see if excluded
			 * before reporting an error */
			if (check_exclude_file(fname, 0, exclude_level)) {
				/* file is excluded anyway, ignore silently */
				return NULL;
			}
		}
		io_error |= IOERR_GENERAL;
		rprintf(FERROR, "readlink %s failed: %s\n",
			full_fname(fname), strerror(save_errno));
		return NULL;
	}

	/* backup.c calls us with exclude_level set to NO_EXCLUDES. */
	if (exclude_level == NO_EXCLUDES)
		goto skip_excludes;

	if (S_ISDIR(st.st_mode) && !recurse && !files_from) {
		rprintf(FINFO, "skipping directory %s\n", fname);
		return NULL;
	}

	if (one_file_system && st.st_dev != filesystem_dev) {
		if (skip_filesystem(fname, &st))
			return NULL;
	}

	if (check_exclude_file(fname, S_ISDIR(st.st_mode) != 0, exclude_level))
		return NULL;

	if (lp_ignore_nonreadable(module_id) && access(fname, R_OK) != 0)
		return NULL;

      skip_excludes:

	if (verbose > 2)
		rprintf(FINFO, "make_file(%s,*,%d)\n", fname, exclude_level);

	file = new(struct file_struct);
	if (!file)
		out_of_memory("make_file");
	memset((char *) file, 0, sizeof(*file));

	if ((p = strrchr(fname, '/'))) {
		static char *lastdir;
		*p = 0;
		if (lastdir && strcmp(fname, lastdir) == 0) {
			file->dirname = lastdir;
		} else {
			file->dirname = strdup(fname);
			lastdir = file->dirname;
		}
		file->basename = STRDUP(ap, p + 1);
		*p = '/';
	} else {
		file->dirname = NULL;
		file->basename = STRDUP(ap, fname);
	}

	file->modtime = st.st_mtime;
	file->length = st.st_size;
	file->mode = st.st_mode;
	file->uid = st.st_uid;
	file->gid = st.st_gid;
	file->dev = st.st_dev;
	file->inode = st.st_ino;
#ifdef HAVE_STRUCT_STAT_ST_RDEV
	file->rdev = st.st_rdev;
#endif

#if SUPPORT_LINKS
	if (S_ISLNK(st.st_mode)) {
		file->link = STRDUP(ap, linkbuf);
	}
#endif

	if (always_checksum) {
		file->sum = (char *) MALLOC(ap, MD4_SUM_LENGTH);
		if (!file->sum)
			out_of_memory("md4 sum");
		/* drat. we have to provide a null checksum for non-regular
		   files in order to be compatible with earlier versions
		   of rsync */
		if (S_ISREG(st.st_mode)) {
			file_checksum(fname, file->sum, st.st_size);
		} else {
			memset(file->sum, 0, MD4_SUM_LENGTH);
		}
	}

	if (flist_dir) {
		static char *lastdir;
		if (lastdir && strcmp(lastdir, flist_dir) == 0) {
			file->basedir = lastdir;
		} else {
			file->basedir = strdup(flist_dir);
			lastdir = file->basedir;
		}
	} else {
		file->basedir = NULL;
	}

	if (!S_ISDIR(st.st_mode))
		stats.total_size += st.st_size;

	return file;
}
