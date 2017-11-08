int set_file_attrs(char *fname, struct file_struct *file, STRUCT_STAT *st,
		   int flags)
{
	int updated = 0;
	STRUCT_STAT st2;
	int change_uid, change_gid;

	if (!st) {
		if (dry_run)
			return 1;
		if (link_stat(fname, &st2, 0) < 0) {
			rsyserr(FERROR, errno, "stat %s failed",
				full_fname(fname));
			return 0;
		}
		st = &st2;
		if (!preserve_perms && S_ISDIR(file->mode)
		 && st->st_mode & S_ISGID) {
			/* We just created this directory and its setgid
			 * bit is on, so make sure it stays on. */
			file->mode |= S_ISGID;
		}
	}

	if (!preserve_times || (S_ISDIR(st->st_mode) && omit_dir_times))
		flags |= ATTRS_SKIP_MTIME;
	if (!(flags & ATTRS_SKIP_MTIME)
	    && cmp_time(st->st_mtime, file->modtime) != 0) {
		int ret = set_modtime(fname, file->modtime, st->st_mode);
		if (ret < 0) {
			rsyserr(FERROR, errno, "failed to set times on %s",
				full_fname(fname));
			return 0;
		}
		if (ret == 0) /* ret == 1 if symlink could not be set */
			updated = 1;
	}

	change_uid = am_root && preserve_uid && st->st_uid != file->uid;
	change_gid = preserve_gid && file->gid != GID_NONE
		&& st->st_gid != file->gid;
#if !defined HAVE_LCHOWN && !defined CHOWN_MODIFIES_SYMLINK
	if (S_ISLNK(st->st_mode))
		;
	else
#endif
	if (change_uid || change_gid) {
		if (verbose > 2) {
			if (change_uid) {
				rprintf(FINFO,
					"set uid of %s from %ld to %ld\n",
					fname,
					(long)st->st_uid, (long)file->uid);
			}
			if (change_gid) {
				rprintf(FINFO,
					"set gid of %s from %ld to %ld\n",
					fname,
					(long)st->st_gid, (long)file->gid);
			}
		}
		if (do_lchown(fname,
		    change_uid ? file->uid : st->st_uid,
		    change_gid ? file->gid : st->st_gid) != 0) {
			/* shouldn't have attempted to change uid or gid
			 * unless have the privilege */
			rsyserr(FERROR, errno, "%s %s failed",
			    change_uid ? "chown" : "chgrp",
			    full_fname(fname));
			return 0;
		}
		/* a lchown had been done - we have to re-stat if the
		 * destination had the setuid or setgid bits set due
		 * to the side effect of the chown call */
		if (st->st_mode & (S_ISUID | S_ISGID)) {
			link_stat(fname, st,
				  keep_dirlinks && S_ISDIR(st->st_mode));
		}
		updated = 1;
	}

#ifdef HAVE_CHMOD
	if ((st->st_mode & CHMOD_BITS) != (file->mode & CHMOD_BITS)) {
		int ret = do_chmod(fname, file->mode);
		if (ret < 0) {
			rsyserr(FERROR, errno,
				"failed to set permissions on %s",
				full_fname(fname));
			return 0;
		}
		if (ret == 0) /* ret == 1 if symlink could not be set */
			updated = 1;
	}
#endif

	if (verbose > 1 && flags & ATTRS_REPORT) {
		enum logcode code = daemon_log_format_has_i || dry_run
				  ? FCLIENT : FINFO;
		if (updated)
			rprintf(code, "%s\n", fname);
		else
			rprintf(code, "%s is uptodate\n", fname);
	}
	return updated;
}