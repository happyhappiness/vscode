int set_perms(char *fname,struct file_struct *file,STRUCT_STAT *st,
		int report)
{
	int updated = 0;
	STRUCT_STAT st2;
	int change_uid, change_gid;

	if (dry_run) return 0;

	if (!st) {
		if (link_stat(fname,&st2) != 0) {
			rprintf(FERROR, "stat %s failed: %s\n",
				full_fname(fname), strerror(errno));
			return 0;
		}
		st = &st2;
	}

	if (preserve_times && !S_ISLNK(st->st_mode) &&
	    cmp_modtime(st->st_mtime, file->modtime) != 0) {
		/* don't complain about not setting times on directories
		   because some filesystems can't do it */
		if (set_modtime(fname,file->modtime) != 0 &&
		    !S_ISDIR(st->st_mode)) {
			rprintf(FERROR, "failed to set times on %s: %s\n",
				full_fname(fname), strerror(errno));
			return 0;
		} else {
			updated = 1;
		}
	}

	change_uid = am_root && preserve_uid && st->st_uid != file->uid;
	change_gid = preserve_gid && file->gid != (gid_t) -1 && \
				st->st_gid != file->gid;
	if (change_gid && !am_root) {
		/* enforce bsd-style group semantics: non-root can only
		    change to groups that the user is a member of */
		change_gid = is_in_group(file->gid);
	}
	if (change_uid || change_gid) {
		if (do_lchown(fname,
			      change_uid?file->uid:st->st_uid,
			      change_gid?file->gid:st->st_gid) != 0) {
			/* shouldn't have attempted to change uid or gid
			     unless have the privilege */
			rprintf(FERROR, "chown %s failed: %s\n",
				full_fname(fname), strerror(errno));
			return 0;
		}
		/* a lchown had been done - we have to re-stat if the
                   destination had the setuid or setgid bits set due
                   to the side effect of the chown call */
		if (st->st_mode & (S_ISUID | S_ISGID)) {
			link_stat(fname, st);
		}
		updated = 1;
	}

#ifdef HAVE_CHMOD
	if (!S_ISLNK(st->st_mode)) {
		if ((st->st_mode & CHMOD_BITS) != (file->mode & CHMOD_BITS)) {
			updated = 1;
			if (do_chmod(fname,(file->mode & CHMOD_BITS)) != 0) {
				rprintf(FERROR, "failed to set permissions on %s: %s\n",
					full_fname(fname), strerror(errno));
				return 0;
			}
		}
	}
#endif

	if (verbose > 1 && report) {
		if (updated)
			rprintf(FINFO,"%s\n",fname);
		else
			rprintf(FINFO,"%s is uptodate\n",fname);
	}
	return updated;
}