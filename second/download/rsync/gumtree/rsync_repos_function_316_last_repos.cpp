int atomic_create(struct file_struct *file, char *fname, const char *slnk, const char *hlnk,
		  dev_t rdev, stat_x *sxp, int del_for_flag)
{
	char tmpname[MAXPATHLEN];
	const char *create_name;
	int skip_atomic, dir_in_the_way = del_for_flag && S_ISDIR(sxp->st.st_mode);

	if (!del_for_flag || dir_in_the_way || tmpdir || !get_tmpname(tmpname, fname, True))
		skip_atomic = 1;
	else
		skip_atomic = 0;

	if (del_for_flag) {
		if (make_backups > 0 && !dir_in_the_way) {
			if (!make_backup(fname, skip_atomic))
				return 0;
		} else if (skip_atomic) {
			int del_opts = delete_mode || force_delete ? DEL_RECURSE : 0;
			if (delete_item(fname, sxp->st.st_mode, del_opts | del_for_flag) != 0)
				return 0;
		}
	}

	create_name = skip_atomic ? fname : tmpname;

	if (slnk) {
#ifdef SUPPORT_LINKS
		if (do_symlink(slnk, create_name) < 0) {
			rsyserr(FERROR_XFER, errno, "symlink %s -> \"%s\" failed",
				full_fname(create_name), slnk);
			return 0;
		}
#else
		return 0;
#endif
	} else if (hlnk) {
#ifdef SUPPORT_HARD_LINKS
		if (!hard_link_one(file, create_name, hlnk, 0))
			return 0;
#else
		return 0;
#endif
	} else {
		if (do_mknod(create_name, file->mode, rdev) < 0) {
			rsyserr(FERROR_XFER, errno, "mknod %s failed",
				full_fname(create_name));
			return 0;
		}
	}

	if (!skip_atomic) {
		if (do_rename(tmpname, fname) < 0) {
			rsyserr(FERROR_XFER, errno, "rename %s -> \"%s\" failed",
				full_fname(tmpname), full_fname(fname));
			do_unlink(tmpname);
			return 0;
		}
	}

	return 1;
}