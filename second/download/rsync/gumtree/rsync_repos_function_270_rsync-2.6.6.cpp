int set_perms(char *fname,struct file_struct *file,STRUCT_STAT *st,
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
	}

	if (!preserve_times || S_ISLNK(st->st_mode)
	 || (S_ISDIR(st->st_mode) && omit_dir_times))
		flags |= PERMS_SKIP_MTIME;
	if (!(flags & PERMS_SKIP_MTIME)
	    && cmp_modtime(st->st_mtime, file->modtime) != 0) {
		if (set_modtime(fname,file->modtime) != 0) {
			rsyserr(FERROR, errno, "failed to set times on %s",
				full_fname(fname));
			return 0;
		}
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
					safe_fname(fname),
					(long)st->st_uid, (long)file->uid);
			}
			if (change_gid) {
				rprintf(FINFO,
					"set gid of %s from %ld to %ld\n",
					safe_fname(fname),
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
	if (!S_ISLNK(st->st_mode)) {
		if ((st->st_mode & CHMOD_BITS) != (file->mode & CHMOD_BITS)) {
			updated = 1;
			if (do_chmod(fname,(file->mode & CHMOD_BITS)) != 0) {
				rsyserr(FERROR, errno, "failed to set permissions on %s",
					full_fname(fname));
				return 0;
			}
		}
	}
#endif

	if (verbose > 1 && flags & PERMS_REPORT) {
		enum logcode code = daemon_log_format_has_i || dry_run
				  ? FCLIENT : FINFO;
		if (updated)
			rprintf(code, "%s\n", safe_fname(fname));
		else
			rprintf(code, "%s is uptodate\n", safe_fname(fname));
	}
	return updated;
}