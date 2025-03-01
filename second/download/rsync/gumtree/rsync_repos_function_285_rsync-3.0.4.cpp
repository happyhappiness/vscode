static void recv_generator(char *fname, struct file_struct *file, int ndx,
			   int itemizing, enum logcode code, int f_out)
{
	static const char *parent_dirname = "";
	/* Missing dir not created due to --dry-run; will still be scanned. */
	static struct file_struct *dry_missing_dir = NULL;
	/* Missing dir whose contents are skipped altogether due to
	 * --ignore-non-existing, daemon exclude, or mkdir failure. */
	static struct file_struct *skip_dir = NULL;
	static struct file_list *fuzzy_dirlist = NULL;
	static int need_fuzzy_dirlist = 0;
	struct file_struct *fuzzy_file = NULL;
	int fd = -1, f_copy = -1;
	stat_x sx, real_sx;
	STRUCT_STAT partial_st;
	struct file_struct *back_file = NULL;
	int statret, real_ret, stat_errno;
	char *fnamecmp, *partialptr, *backupptr = NULL;
	char fnamecmpbuf[MAXPATHLEN];
	uchar fnamecmp_type;
	int del_opts = delete_mode || force_delete ? DEL_RECURSE : 0;
	int is_dir = !S_ISDIR(file->mode) ? 0
		   : inc_recurse && ndx != cur_flist->ndx_start - 1 ? -1
		   : 1;

	if (verbose > 2)
		rprintf(FINFO, "recv_generator(%s,%d)\n", fname, ndx);

	if (list_only) {
		if (is_dir < 0
		 || (is_dir && !implied_dirs && file->flags & FLAG_IMPLIED_DIR))
			return;
		list_file_entry(file);
		return;
	}

	if (skip_dir) {
		if (is_below(file, skip_dir)) {
			if (is_dir)
				file->flags |= FLAG_MISSING_DIR;
#ifdef SUPPORT_HARD_LINKS
			else if (F_IS_HLINKED(file))
				handle_skipped_hlink(file, itemizing, code, f_out);
#endif
			return;
		}
		skip_dir = NULL;
	}

	if (daemon_filter_list.head && (*fname != '.' || fname[1])) {
		if (check_filter(&daemon_filter_list, FLOG, fname, is_dir) < 0) {
			if (is_dir < 0)
				return;
#ifdef SUPPORT_HARD_LINKS
			if (F_IS_HLINKED(file))
				handle_skipped_hlink(file, itemizing, code, f_out);
#endif
			rprintf(FERROR_XFER,
				"skipping daemon-excluded %s \"%s\"\n",
				is_dir ? "directory" : "file", fname);
			if (is_dir)
				goto skipping_dir_contents;
			return;
		}
	}

#ifdef SUPPORT_ACLS
	sx.acc_acl = sx.def_acl = NULL;
#endif
#ifdef SUPPORT_XATTRS
	sx.xattr = NULL;
#endif
	if (dry_run > 1 || (dry_missing_dir && is_below(file, dry_missing_dir))) {
	  parent_is_dry_missing:
		if (fuzzy_dirlist) {
			flist_free(fuzzy_dirlist);
			fuzzy_dirlist = NULL;
		}
		parent_dirname = "";
		statret = -1;
		stat_errno = ENOENT;
	} else {
		const char *dn = file->dirname ? file->dirname : ".";
		dry_missing_dir = NULL;
		if (parent_dirname != dn && strcmp(parent_dirname, dn) != 0) {
			if (relative_paths && !implied_dirs
			 && do_stat(dn, &sx.st) < 0) {
				if (dry_run)
					goto parent_is_dry_missing;
				if (create_directory_path(fname) < 0) {
					rsyserr(FERROR_XFER, errno,
						"recv_generator: mkdir %s failed",
						full_fname(dn));
				}
			}
			if (fuzzy_dirlist) {
				flist_free(fuzzy_dirlist);
				fuzzy_dirlist = NULL;
			}
			if (fuzzy_basis)
				need_fuzzy_dirlist = 1;
#ifdef SUPPORT_ACLS
			if (!preserve_perms)
				dflt_perms = default_perms_for_dir(dn);
#endif
		}
		parent_dirname = dn;

		if (need_fuzzy_dirlist && S_ISREG(file->mode)) {
			strlcpy(fnamecmpbuf, dn, sizeof fnamecmpbuf);
			fuzzy_dirlist = get_dirlist(fnamecmpbuf, -1, 1);
			need_fuzzy_dirlist = 0;
		}

		statret = link_stat(fname, &sx.st, keep_dirlinks && is_dir);
		stat_errno = errno;
	}

	if (ignore_non_existing > 0 && statret == -1 && stat_errno == ENOENT) {
		if (is_dir) {
			if (is_dir < 0)
				return;
			skip_dir = file;
			file->flags |= FLAG_MISSING_DIR;
		}
#ifdef SUPPORT_HARD_LINKS
		else if (F_IS_HLINKED(file))
			handle_skipped_hlink(file, itemizing, code, f_out);
#endif
		if (verbose > 1) {
			rprintf(FINFO, "not creating new %s \"%s\"\n",
				is_dir ? "directory" : "file", fname);
		}
		return;
	}

	if (statret == 0 && !(sx.st.st_mode & S_IWUSR)
	 && !am_root && sx.st.st_uid == our_uid)
		del_opts |= DEL_NO_UID_WRITE;

	if (ignore_existing > 0 && statret == 0
	 && (!is_dir || !S_ISDIR(sx.st.st_mode))) {
		if (verbose > 1 && is_dir >= 0)
			rprintf(FINFO, "%s exists\n", fname);
#ifdef SUPPORT_HARD_LINKS
		if (F_IS_HLINKED(file))
			handle_skipped_hlink(file, itemizing, code, f_out);
#endif
		goto cleanup;
	}

	if (is_dir) {
		if (!implied_dirs && file->flags & FLAG_IMPLIED_DIR)
			goto cleanup;
		if (is_dir < 0) {
			/* In inc_recurse mode we want to make sure any missing
			 * directories get created while we're still processing
			 * the parent dir (which allows us to touch the parent
			 * dir's mtime right away).  We will handle the dir in
			 * full later (right before we handle its contents). */
			if (statret == 0
			 && (S_ISDIR(sx.st.st_mode)
			  || delete_item(fname, sx.st.st_mode, del_opts | DEL_FOR_DIR) != 0))
				goto cleanup; /* Any errors get reported later. */
			if (do_mkdir(fname, file->mode & 0700) == 0)
				file->flags |= FLAG_DIR_CREATED;
			goto cleanup;
		}
		/* The file to be received is a directory, so we need
		 * to prepare appropriately.  If there is already a
		 * file of that name and it is *not* a directory, then
		 * we need to delete it.  If it doesn't exist, then
		 * (perhaps recursively) create it. */
		if (statret == 0 && !S_ISDIR(sx.st.st_mode)) {
			if (delete_item(fname, sx.st.st_mode, del_opts | DEL_FOR_DIR) != 0)
				goto skipping_dir_contents;
			statret = -1;
		}
		if (dry_run && statret != 0) {
			if (!dry_missing_dir)
				dry_missing_dir = file;
			file->flags |= FLAG_MISSING_DIR;
		}
		real_ret = statret;
		real_sx = sx;
		if (file->flags & FLAG_DIR_CREATED)
			statret = -1;
		if (!preserve_perms) { /* See comment in non-dir code below. */
			file->mode = dest_mode(file->mode, sx.st.st_mode,
					       dflt_perms, statret == 0);
		}
		if (statret != 0 && basis_dir[0] != NULL) {
			int j = try_dests_non(file, fname, ndx, fnamecmpbuf, &sx,
					      itemizing, code);
			if (j == -2) {
				itemizing = 0;
				code = FNONE;
				statret = 1;
			} else if (j >= 0)
				statret = 1;
		}
		if (itemizing && f_out != -1) {
			itemize(fname, file, ndx, statret, &sx,
				statret ? ITEM_LOCAL_CHANGE : 0, 0, NULL);
		}
		if (real_ret != 0 && do_mkdir(fname,file->mode) < 0 && errno != EEXIST) {
			if (!relative_paths || errno != ENOENT
			    || create_directory_path(fname) < 0
			    || (do_mkdir(fname, file->mode) < 0 && errno != EEXIST)) {
				rsyserr(FERROR_XFER, errno,
					"recv_generator: mkdir %s failed",
					full_fname(fname));
			  skipping_dir_contents:
				rprintf(FERROR,
				    "*** Skipping any contents from this failed directory ***\n");
				skip_dir = file;
				file->flags |= FLAG_MISSING_DIR;
				goto cleanup;
			}
		}
#ifdef SUPPORT_XATTRS
		if (preserve_xattrs && statret == 1)
			copy_xattrs(fnamecmpbuf, fname);
#endif
		if (set_file_attrs(fname, file, real_ret ? NULL : &real_sx, NULL, 0)
		    && verbose && code != FNONE && f_out != -1)
			rprintf(code, "%s/\n", fname);

		/* We need to ensure that the dirs in the transfer have writable
		 * permissions during the time we are putting files within them.
		 * This is then fixed after the transfer is done. */
#ifdef HAVE_CHMOD
		if (!am_root && !(file->mode & S_IWUSR) && dir_tweaking) {
			mode_t mode = file->mode | S_IWUSR;
			if (do_chmod(fname, mode) < 0) {
				rsyserr(FERROR_XFER, errno,
					"failed to modify permissions on %s",
					full_fname(fname));
			}
			need_retouch_dir_perms = 1;
		}
#endif

		if (real_ret != 0 && one_file_system)
			real_sx.st.st_dev = filesystem_dev;
		if (inc_recurse) {
			if (one_file_system) {
				uint32 *devp = F_DIR_DEV_P(file);
				DEV_MAJOR(devp) = major(real_sx.st.st_dev);
				DEV_MINOR(devp) = minor(real_sx.st.st_dev);
			}
		}
		else if (delete_during && f_out != -1 && !phase
		    && !(file->flags & FLAG_MISSING_DIR)) {
			if (file->flags & FLAG_CONTENT_DIR)
				delete_in_dir(fname, file, &real_sx.st.st_dev);
			else
				change_local_filter_dir(fname, strlen(fname), F_DEPTH(file));
		}
		goto cleanup;
	}

	/* If we're not preserving permissions, change the file-list's
	 * mode based on the local permissions and some heuristics. */
	if (!preserve_perms) {
		int exists = statret == 0 && !S_ISDIR(sx.st.st_mode);
		file->mode = dest_mode(file->mode, sx.st.st_mode, dflt_perms,
				       exists);
	}

#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && F_HLINK_NOT_FIRST(file)
	 && hard_link_check(file, ndx, fname, statret, &sx, itemizing, code))
		goto cleanup;
#endif

	if (preserve_links && S_ISLNK(file->mode)) {
#ifdef SUPPORT_LINKS
		const char *sl = F_SYMLINK(file);
		if (safe_symlinks && unsafe_symlink(sl, fname)) {
			if (verbose) {
				if (solo_file)
					fname = f_name(file, NULL);
				rprintf(FINFO,
					"ignoring unsafe symlink %s -> \"%s\"\n",
					full_fname(fname), sl);
			}
			return;
		}
		if (statret == 0) {
			char lnk[MAXPATHLEN];
			int len;

			if (!S_ISLNK(sx.st.st_mode))
				statret = -1;
			else if ((len = readlink(fname, lnk, MAXPATHLEN-1)) > 0
			      && strncmp(lnk, sl, len) == 0 && sl[len] == '\0') {
				/* The link is pointing to the right place. */
				set_file_attrs(fname, file, &sx, NULL, maybe_ATTRS_REPORT);
				if (itemizing)
					itemize(fname, file, ndx, 0, &sx, 0, 0, NULL);
#if defined SUPPORT_HARD_LINKS && defined CAN_HARDLINK_SYMLINK
				if (preserve_hard_links && F_IS_HLINKED(file))
					finish_hard_link(file, fname, ndx, &sx.st, itemizing, code, -1);
#endif
				if (remove_source_files == 1)
					goto return_with_success;
				goto cleanup;
			}
			/* Not the right symlink (or not a symlink), so
			 * delete it. */
			if (delete_item(fname, sx.st.st_mode, del_opts | DEL_FOR_SYMLINK) != 0)
				goto cleanup;
		} else if (basis_dir[0] != NULL) {
			int j = try_dests_non(file, fname, ndx, fnamecmpbuf, &sx,
					      itemizing, code);
			if (j == -2) {
#ifndef CAN_HARDLINK_SYMLINK
				if (link_dest) {
					/* Resort to --copy-dest behavior. */
				} else
#endif
				if (!copy_dest)
					goto cleanup;
				itemizing = 0;
				code = FNONE;
			} else if (j >= 0)
				statret = 1;
		}
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && F_HLINK_NOT_LAST(file)) {
			cur_flist->in_progress++;
			goto cleanup;
		}
#endif
		if (do_symlink(sl, fname) != 0) {
			rsyserr(FERROR_XFER, errno, "symlink %s -> \"%s\" failed",
				full_fname(fname), sl);
		} else {
			set_file_attrs(fname, file, NULL, NULL, 0);
			if (itemizing) {
				itemize(fname, file, ndx, statret, &sx,
					ITEM_LOCAL_CHANGE|ITEM_REPORT_CHANGE, 0, NULL);
			}
			if (code != FNONE && verbose)
				rprintf(code, "%s -> %s\n", fname, sl);
#ifdef SUPPORT_HARD_LINKS
			if (preserve_hard_links && F_IS_HLINKED(file))
				finish_hard_link(file, fname, ndx, NULL, itemizing, code, -1);
#endif
			/* This does not check remove_source_files == 1
			 * because this is one of the items that the old
			 * --remove-sent-files option would remove. */
			if (remove_source_files)
				goto return_with_success;
		}
#endif
		goto cleanup;
	}

	if ((am_root && preserve_devices && IS_DEVICE(file->mode))
	 || (preserve_specials && IS_SPECIAL(file->mode))) {
		uint32 *devp = F_RDEV_P(file);
		dev_t rdev = MAKEDEV(DEV_MAJOR(devp), DEV_MINOR(devp));
		if (statret == 0) {
			int del_for_flag;
			if (IS_DEVICE(file->mode)) {
				if (!IS_DEVICE(sx.st.st_mode))
					statret = -1;
				del_for_flag = DEL_FOR_DEVICE;
			} else {
				if (!IS_SPECIAL(sx.st.st_mode))
					statret = -1;
				del_for_flag = DEL_FOR_SPECIAL;
			}
			if (statret == 0
			 && BITS_EQUAL(sx.st.st_mode, file->mode, _S_IFMT)
			 && sx.st.st_rdev == rdev) {
				/* The device or special file is identical. */
				set_file_attrs(fname, file, &sx, NULL, maybe_ATTRS_REPORT);
				if (itemizing)
					itemize(fname, file, ndx, 0, &sx, 0, 0, NULL);
#ifdef SUPPORT_HARD_LINKS
				if (preserve_hard_links && F_IS_HLINKED(file))
					finish_hard_link(file, fname, ndx, &sx.st, itemizing, code, -1);
#endif
				if (remove_source_files == 1)
					goto return_with_success;
				goto cleanup;
			}
			if (delete_item(fname, sx.st.st_mode, del_opts | del_for_flag) != 0)
				goto cleanup;
		} else if (basis_dir[0] != NULL) {
			int j = try_dests_non(file, fname, ndx, fnamecmpbuf, &sx,
					      itemizing, code);
			if (j == -2) {
#ifndef CAN_HARDLINK_SPECIAL
				if (link_dest) {
					/* Resort to --copy-dest behavior. */
				} else
#endif
				if (!copy_dest)
					goto cleanup;
				itemizing = 0;
				code = FNONE;
			} else if (j >= 0)
				statret = 1;
		}
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && F_HLINK_NOT_LAST(file)) {
			cur_flist->in_progress++;
			goto cleanup;
		}
#endif
		if (verbose > 2) {
			rprintf(FINFO, "mknod(%s, 0%o, [%ld,%ld])\n",
				fname, (int)file->mode,
				(long)major(rdev), (long)minor(rdev));
		}
		if (do_mknod(fname, file->mode, rdev) < 0) {
			rsyserr(FERROR_XFER, errno, "mknod %s failed",
				full_fname(fname));
		} else {
			set_file_attrs(fname, file, NULL, NULL, 0);
			if (itemizing) {
				itemize(fname, file, ndx, statret, &sx,
					ITEM_LOCAL_CHANGE|ITEM_REPORT_CHANGE, 0, NULL);
			}
			if (code != FNONE && verbose)
				rprintf(code, "%s\n", fname);
#ifdef SUPPORT_HARD_LINKS
			if (preserve_hard_links && F_IS_HLINKED(file))
				finish_hard_link(file, fname, ndx, NULL, itemizing, code, -1);
#endif
			if (remove_source_files == 1)
				goto return_with_success;
		}
		goto cleanup;
	}

	if (!S_ISREG(file->mode)) {
		if (solo_file)
			fname = f_name(file, NULL);
		rprintf(FINFO, "skipping non-regular file \"%s\"\n", fname);
		goto cleanup;
	}

	if (max_size > 0 && F_LENGTH(file) > max_size) {
		if (verbose > 1) {
			if (solo_file)
				fname = f_name(file, NULL);
			rprintf(FINFO, "%s is over max-size\n", fname);
		}
		goto cleanup;
	}
	if (min_size > 0 && F_LENGTH(file) < min_size) {
		if (verbose > 1) {
			if (solo_file)
				fname = f_name(file, NULL);
			rprintf(FINFO, "%s is under min-size\n", fname);
		}
		goto cleanup;
	}

	if (update_only > 0 && statret == 0
	    && cmp_time(sx.st.st_mtime, file->modtime) > 0) {
		if (verbose > 1)
			rprintf(FINFO, "%s is newer\n", fname);
#ifdef SUPPORT_HARD_LINKS
		if (F_IS_HLINKED(file))
			handle_skipped_hlink(file, itemizing, code, f_out);
#endif
		goto cleanup;
	}

	fnamecmp = fname;
	fnamecmp_type = FNAMECMP_FNAME;

	if (statret == 0 && !S_ISREG(sx.st.st_mode)) {
		if (delete_item(fname, sx.st.st_mode, del_opts | DEL_FOR_FILE) != 0)
			goto cleanup;
		statret = -1;
		stat_errno = ENOENT;
	}

	if (statret != 0 && basis_dir[0] != NULL) {
		int j = try_dests_reg(file, fname, ndx, fnamecmpbuf, &sx,
				      itemizing, code);
		if (j == -2) {
			if (remove_source_files == 1)
				goto return_with_success;
			goto cleanup;
		}
		if (j >= 0) {
			fnamecmp = fnamecmpbuf;
			fnamecmp_type = j;
			statret = 0;
		}
	}

	real_ret = statret;
	real_sx = sx;

	if (partial_dir && (partialptr = partial_dir_fname(fname)) != NULL
	    && link_stat(partialptr, &partial_st, 0) == 0
	    && S_ISREG(partial_st.st_mode)) {
		if (statret != 0)
			goto prepare_to_open;
	} else
		partialptr = NULL;

	if (statret != 0 && fuzzy_dirlist) {
		int j = find_fuzzy(file, fuzzy_dirlist);
		if (j >= 0) {
			fuzzy_file = fuzzy_dirlist->files[j];
			f_name(fuzzy_file, fnamecmpbuf);
			if (verbose > 2) {
				rprintf(FINFO, "fuzzy basis selected for %s: %s\n",
					fname, fnamecmpbuf);
			}
			sx.st.st_size = F_LENGTH(fuzzy_file);
			statret = 0;
			fnamecmp = fnamecmpbuf;
			fnamecmp_type = FNAMECMP_FUZZY;
		}
	}

	if (statret != 0) {
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && F_HLINK_NOT_LAST(file)) {
			cur_flist->in_progress++;
			goto cleanup;
		}
#endif
		if (stat_errno == ENOENT)
			goto notify_others;
		rsyserr(FERROR_XFER, stat_errno, "recv_generator: failed to stat %s",
			full_fname(fname));
		goto cleanup;
	}

	if (fnamecmp_type <= FNAMECMP_BASIS_DIR_HIGH)
		;
	else if (fnamecmp_type == FNAMECMP_FUZZY)
		;
	else if (unchanged_file(fnamecmp, file, &sx.st)) {
		if (partialptr) {
			do_unlink(partialptr);
			handle_partial_dir(partialptr, PDIR_DELETE);
		}
		set_file_attrs(fname, file, &sx, NULL, maybe_ATTRS_REPORT);
		if (itemizing)
			itemize(fnamecmp, file, ndx, statret, &sx, 0, 0, NULL);
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && F_IS_HLINKED(file))
			finish_hard_link(file, fname, ndx, &sx.st, itemizing, code, -1);
#endif
		if (remove_source_files != 1)
			goto cleanup;
	  return_with_success:
		if (!dry_run)
			send_msg_int(MSG_SUCCESS, ndx);
		goto cleanup;
	}

	if (append_mode > 0 && sx.st.st_size >= F_LENGTH(file)) {
#ifdef SUPPORT_HARD_LINKS
		if (F_IS_HLINKED(file))
			handle_skipped_hlink(file, itemizing, code, f_out);
#endif
		goto cleanup;
	}

  prepare_to_open:
	if (partialptr) {
		sx.st = partial_st;
		fnamecmp = partialptr;
		fnamecmp_type = FNAMECMP_PARTIAL_DIR;
		statret = 0;
	}

	if (!do_xfers)
		goto notify_others;

	if (read_batch || whole_file) {
		if (inplace && make_backups > 0 && fnamecmp_type == FNAMECMP_FNAME) {
			if (!(backupptr = get_backup_name(fname)))
				goto cleanup;
			if (!(back_file = make_file(fname, NULL, NULL, 0, NO_FILTERS)))
				goto pretend_missing;
			if (copy_file(fname, backupptr, -1, back_file->mode, 1) < 0) {
				unmake_file(back_file);
				back_file = NULL;
				goto cleanup;
			}
		}
		goto notify_others;
	}

	if (fuzzy_dirlist) {
		int j = flist_find(fuzzy_dirlist, file);
		if (j >= 0) /* don't use changing file as future fuzzy basis */
			fuzzy_dirlist->files[j]->flags |= FLAG_FILE_SENT;
	}

	/* open the file */
	if ((fd = do_open(fnamecmp, O_RDONLY, 0)) < 0) {
		rsyserr(FERROR, errno, "failed to open %s, continuing",
			full_fname(fnamecmp));
	  pretend_missing:
		/* pretend the file didn't exist */
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && F_HLINK_NOT_LAST(file)) {
			cur_flist->in_progress++;
			goto cleanup;
		}
#endif
		statret = real_ret = -1;
		goto notify_others;
	}

	if (inplace && make_backups > 0 && fnamecmp_type == FNAMECMP_FNAME) {
		if (!(backupptr = get_backup_name(fname))) {
			close(fd);
			goto cleanup;
		}
		if (!(back_file = make_file(fname, NULL, NULL, 0, NO_FILTERS))) {
			close(fd);
			goto pretend_missing;
		}
		if (robust_unlink(backupptr) && errno != ENOENT) {
			rsyserr(FERROR_XFER, errno, "unlink %s",
				full_fname(backupptr));
			unmake_file(back_file);
			back_file = NULL;
			close(fd);
			goto cleanup;
		}
		if ((f_copy = do_open(backupptr, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0600)) < 0) {
			int save_errno = errno ? errno : EINVAL; /* 0 paranoia */
			if (errno == ENOENT && make_bak_dir(backupptr) == 0) {
				if ((f_copy = do_open(backupptr, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0600)) < 0)
					save_errno = errno ? errno : save_errno;
				else
					save_errno = 0;
			}
			if (save_errno) {
				rsyserr(FERROR_XFER, save_errno, "open %s", full_fname(backupptr));
				unmake_file(back_file);
				back_file = NULL;
				close(fd);
				goto cleanup;
			}
		}
		fnamecmp_type = FNAMECMP_BACKUP;
	}

	if (verbose > 3) {
		rprintf(FINFO, "gen mapped %s of size %.0f\n",
			fnamecmp, (double)sx.st.st_size);
	}

	if (verbose > 2)
		rprintf(FINFO, "generating and sending sums for %d\n", ndx);

  notify_others:
	if (remove_source_files && !delay_updates && !phase && !dry_run)
		increment_active_files(ndx, itemizing, code);
	if (inc_recurse && !dry_run)
		cur_flist->in_progress++;
#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && F_IS_HLINKED(file))
		file->flags |= FLAG_FILE_SENT;
#endif
	write_ndx(f_out, ndx);
	if (itemizing) {
		int iflags = ITEM_TRANSFER;
		if (always_checksum > 0)
			iflags |= ITEM_REPORT_CHANGE;
		if (fnamecmp_type != FNAMECMP_FNAME)
			iflags |= ITEM_BASIS_TYPE_FOLLOWS;
		if (fnamecmp_type == FNAMECMP_FUZZY)
			iflags |= ITEM_XNAME_FOLLOWS;
		itemize(fnamecmp, file, -1, real_ret, &real_sx, iflags, fnamecmp_type,
			fuzzy_file ? fuzzy_file->basename : NULL);
#ifdef SUPPORT_ACLS
		if (preserve_acls)
			free_acl(&real_sx);
#endif
#ifdef SUPPORT_XATTRS
		if (preserve_xattrs)
			free_xattr(&real_sx);
#endif
	}

	if (!do_xfers) {
#ifdef SUPPORT_HARD_LINKS
		if (preserve_hard_links && F_IS_HLINKED(file))
			finish_hard_link(file, fname, ndx, &sx.st, itemizing, code, -1);
#endif
		goto cleanup;
	}
	if (read_batch)
		goto cleanup;

	if (statret != 0 || whole_file)
		write_sum_head(f_out, NULL);
	else if (sx.st.st_size <= 0) {
		write_sum_head(f_out, NULL);
		close(fd);
	} else {
		if (generate_and_send_sums(fd, sx.st.st_size, f_out, f_copy) < 0) {
			rprintf(FWARNING,
			    "WARNING: file is too large for checksum sending: %s\n",
			    fnamecmp);
			write_sum_head(f_out, NULL);
		}
		close(fd);
	}

  cleanup:
	if (back_file) {
		int save_preserve_xattrs = preserve_xattrs;
		if (f_copy >= 0)
			close(f_copy);
#ifdef SUPPORT_XATTRS
		if (preserve_xattrs) {
			copy_xattrs(fname, backupptr);
			preserve_xattrs = 0;
		}
#endif
		set_file_attrs(backupptr, back_file, NULL, NULL, 0);
		preserve_xattrs = save_preserve_xattrs;
		if (verbose > 1) {
			rprintf(FINFO, "backed up %s to %s\n",
				fname, backupptr);
		}
		unmake_file(back_file);
	}

#ifdef SUPPORT_ACLS
	if (preserve_acls)
		free_acl(&sx);
#endif
#ifdef SUPPORT_XATTRS
	if (preserve_xattrs)
		free_xattr(&sx);
#endif
	return;
}