static void recv_generator(char *fname, struct file_struct *file, int ndx,
			   int itemizing, int maybe_ATTRS_REPORT,
			   enum logcode code, int f_out)
{
	static int missing_below = -1, excluded_below = -1;
	static char *parent_dirname = "";
	static struct file_list *fuzzy_dirlist = NULL;
	static int need_fuzzy_dirlist = 0;
	struct file_struct *fuzzy_file = NULL;
	int fd = -1, f_copy = -1;
	STRUCT_STAT st, real_st, partial_st;
	struct file_struct *back_file = NULL;
	int statret, real_ret, stat_errno;
	char *fnamecmp, *partialptr, *backupptr = NULL;
	char fnamecmpbuf[MAXPATHLEN];
	uchar fnamecmp_type;
	int del_opts = DEL_TERSE | (delete_mode ? DEL_FORCE_RECURSE : 0);

	if (list_only)
		return;

	if (!fname) {
		if (fuzzy_dirlist) {
			flist_free(fuzzy_dirlist);
			fuzzy_dirlist = NULL;
		}
		if (missing_below >= 0) {
			dry_run--;
			missing_below = -1;
		}
		parent_dirname = "";
		return;
	}

	if (verbose > 2)
		rprintf(FINFO, "recv_generator(%s,%d)\n", fname, ndx);

	if (server_filter_list.head) {
		if (excluded_below >= 0) {
			if (file->dir.depth > excluded_below)
				goto skipping;
			excluded_below = -1;
		}
		if (check_filter(&server_filter_list, fname,
				 S_ISDIR(file->mode)) < 0) {
			if (S_ISDIR(file->mode))
				excluded_below = file->dir.depth;
		  skipping:
			if (verbose) {
				rprintf(FINFO,
					"skipping server-excluded file \"%s\"\n",
					fname);
			}
			return;
		}
	}

	if (missing_below >= 0 && file->dir.depth <= missing_below) {
		dry_run--;
		missing_below = -1;
	}
	if (dry_run > 1) {
		statret = -1;
		stat_errno = ENOENT;
	} else {
		char *dn = file->dirname ? file->dirname : ".";
		if (parent_dirname != dn && strcmp(parent_dirname, dn) != 0) {
			if (relative_paths && !implied_dirs
			 && do_stat(dn, &st) < 0
			 && create_directory_path(fname) < 0) {
				rsyserr(FERROR, errno,
					"recv_generator: mkdir %s failed",
					full_fname(dn));
			}
			if (fuzzy_dirlist) {
				flist_free(fuzzy_dirlist);
				fuzzy_dirlist = NULL;
			}
			if (fuzzy_basis)
				need_fuzzy_dirlist = 1;
		}
		parent_dirname = dn;

		if (need_fuzzy_dirlist && S_ISREG(file->mode)) {
			fuzzy_dirlist = get_dirlist(dn, -1, 1);
			need_fuzzy_dirlist = 0;
		}

		statret = link_stat(fname, &st,
				    keep_dirlinks && S_ISDIR(file->mode));
		stat_errno = errno;
	}

	if (ignore_non_existing && statret == -1 && stat_errno == ENOENT) {
		if (verbose > 1) {
			rprintf(FINFO, "not creating new %s \"%s\"\n",
				S_ISDIR(file->mode) ? "directory" : "file",
				fname);
		}
		return;
	}

	/* If we're not preserving permissions, change the file-list's
	 * mode based on the local permissions and some heuristics. */
	if (!preserve_perms) {
		int exists = statret == 0
			  && S_ISDIR(st.st_mode) == S_ISDIR(file->mode);
		file->mode = dest_mode(file->mode, st.st_mode, exists);
	}

	if (S_ISDIR(file->mode)) {
		/* The file to be received is a directory, so we need
		 * to prepare appropriately.  If there is already a
		 * file of that name and it is *not* a directory, then
		 * we need to delete it.  If it doesn't exist, then
		 * (perhaps recursively) create it. */
		if (statret == 0 && !S_ISDIR(st.st_mode)) {
			if (delete_item(fname, st.st_mode, del_opts) < 0)
				return;
			statret = -1;
		}
		if (dry_run && statret != 0 && missing_below < 0) {
			missing_below = file->dir.depth;
			dry_run++;
		}
		if (itemizing && f_out != -1) {
			itemize(file, ndx, statret, &st,
				statret ? ITEM_LOCAL_CHANGE : 0, 0, NULL);
		}
		if (statret != 0 && do_mkdir(fname,file->mode) < 0 && errno != EEXIST) {
			if (!relative_paths || errno != ENOENT
			    || create_directory_path(fname) < 0
			    || (do_mkdir(fname, file->mode) < 0 && errno != EEXIST)) {
				rsyserr(FERROR, errno,
					"recv_generator: mkdir %s failed",
					full_fname(fname));
			}
		}
		if (set_file_attrs(fname, file, statret ? NULL : &st, 0)
		    && verbose && code && f_out != -1)
			rprintf(code, "%s/\n", fname);
		if (delete_during && f_out != -1 && !phase && dry_run < 2
		    && (file->flags & FLAG_DEL_HERE))
			delete_in_dir(the_file_list, fname, file, &st);
		return;
	}

	if (preserve_hard_links && file->link_u.links
	    && hard_link_check(file, ndx, fname, statret, &st,
			       itemizing, code, HL_CHECK_MASTER))
		return;

	if (preserve_links && S_ISLNK(file->mode)) {
#ifdef SUPPORT_LINKS
		if (safe_symlinks && unsafe_symlink(file->u.link, fname)) {
			if (verbose) {
				if (the_file_list->count == 1)
					fname = f_name(file, NULL);
				rprintf(FINFO,
					"ignoring unsafe symlink %s -> \"%s\"\n",
					full_fname(fname), file->u.link);
			}
			return;
		}
		if (statret == 0) {
			char lnk[MAXPATHLEN];
			int len;

			if (!S_ISDIR(st.st_mode)
			    && (len = readlink(fname, lnk, MAXPATHLEN-1)) > 0) {
				lnk[len] = 0;
				/* A link already pointing to the
				 * right place -- no further action
				 * required. */
				if (strcmp(lnk, file->u.link) == 0) {
					if (itemizing) {
						itemize(file, ndx, 0, &st, 0,
							0, NULL);
					}
					set_file_attrs(fname, file, &st,
						       maybe_ATTRS_REPORT);
					if (preserve_hard_links
					    && file->link_u.links) {
						hard_link_cluster(file, ndx,
								  itemizing,
								  code);
					}
					return;
				}
			}
			/* Not the right symlink (or not a symlink), so
			 * delete it. */
			if (delete_item(fname, st.st_mode, del_opts) < 0)
				return;
			if (!S_ISLNK(st.st_mode))
				statret = -1;
		} else if (basis_dir[0] != NULL) {
			if (try_dests_non(file, fname, ndx, itemizing,
					  maybe_ATTRS_REPORT, code) == -2) {
#ifndef CAN_HARDLINK_SYMLINK
				if (link_dest) {
					/* Resort to --copy-dest behavior. */
				} else
#endif
				if (!copy_dest)
					return;
				itemizing = code = 0;
			}
		}
		if (preserve_hard_links && file->link_u.links
		    && hard_link_check(file, ndx, fname, -1, &st,
				       itemizing, code, HL_SKIP))
			return;
		if (do_symlink(file->u.link,fname) != 0) {
			rsyserr(FERROR, errno, "symlink %s -> \"%s\" failed",
				full_fname(fname), file->u.link);
		} else {
			set_file_attrs(fname, file, NULL, 0);
			if (itemizing) {
				itemize(file, ndx, statret, &st,
					ITEM_LOCAL_CHANGE, 0, NULL);
			}
			if (code && verbose) {
				rprintf(code, "%s -> %s\n", fname,
					file->u.link);
			}
			if (remove_sent_files && !dry_run) {
				char numbuf[4];
				SIVAL(numbuf, 0, ndx);
				send_msg(MSG_SUCCESS, numbuf, 4);
			}
			if (preserve_hard_links && file->link_u.links)
				hard_link_cluster(file, ndx, itemizing, code);
		}
#endif
		return;
	}

	if ((am_root && preserve_devices && IS_DEVICE(file->mode))
	 || (preserve_specials && IS_SPECIAL(file->mode))) {
		if (statret != 0 && basis_dir[0] != NULL) {
			if (try_dests_non(file, fname, ndx, itemizing,
					  maybe_ATTRS_REPORT, code) == -2) {
#ifndef CAN_HARDLINK_SPECIAL
				if (link_dest) {
					/* Resort to --copy-dest behavior. */
				} else
#endif
				if (!copy_dest)
					return;
				itemizing = code = 0;
			}
		}
		if (statret != 0
		 || (st.st_mode & ~CHMOD_BITS) != (file->mode & ~CHMOD_BITS)
		 || st.st_rdev != file->u.rdev) {
			if (statret == 0
			 && delete_item(fname, st.st_mode, del_opts) < 0)
				return;
			if (preserve_hard_links && file->link_u.links
			    && hard_link_check(file, ndx, fname, -1, &st,
					       itemizing, code, HL_SKIP))
				return;
			if ((IS_DEVICE(file->mode) && !IS_DEVICE(st.st_mode))
			 || (IS_SPECIAL(file->mode) && !IS_SPECIAL(st.st_mode)))
				statret = -1;
			if (verbose > 2) {
				rprintf(FINFO,"mknod(%s,0%o,0x%x)\n",
					fname,
					(int)file->mode, (int)file->u.rdev);
			}
			if (do_mknod(fname,file->mode,file->u.rdev) < 0) {
				rsyserr(FERROR, errno, "mknod %s failed",
					full_fname(fname));
			} else {
				set_file_attrs(fname, file, NULL, 0);
				if (itemizing) {
					itemize(file, ndx, statret, &st,
						ITEM_LOCAL_CHANGE, 0, NULL);
				}
				if (code && verbose)
					rprintf(code, "%s\n", fname);
				if (preserve_hard_links && file->link_u.links) {
					hard_link_cluster(file, ndx,
							  itemizing, code);
				}
			}
		} else {
			if (itemizing)
				itemize(file, ndx, statret, &st, 0, 0, NULL);
			set_file_attrs(fname, file, &st, maybe_ATTRS_REPORT);
			if (preserve_hard_links && file->link_u.links)
				hard_link_cluster(file, ndx, itemizing, code);
		}
		return;
	}

	if (!S_ISREG(file->mode)) {
		if (the_file_list->count == 1)
			fname = f_name(file, NULL);
		rprintf(FINFO, "skipping non-regular file \"%s\"\n", fname);
		return;
	}

	if (max_size && file->length > max_size) {
		if (verbose > 1) {
			if (the_file_list->count == 1)
				fname = f_name(file, NULL);
			rprintf(FINFO, "%s is over max-size\n", fname);
		}
		return;
	}
	if (min_size && file->length < min_size) {
		if (verbose > 1) {
			if (the_file_list->count == 1)
				fname = f_name(file, NULL);
			rprintf(FINFO, "%s is under min-size\n", fname);
		}
		return;
	}

	if (ignore_existing && statret == 0) {
		if (verbose > 1)
			rprintf(FINFO, "%s exists\n", fname);
		return;
	}

	if (update_only && statret == 0
	    && cmp_time(st.st_mtime, file->modtime) > 0) {
		if (verbose > 1)
			rprintf(FINFO, "%s is newer\n", fname);
		return;
	}

	fnamecmp = fname;
	fnamecmp_type = FNAMECMP_FNAME;

	if (statret == 0 && !S_ISREG(st.st_mode)) {
		if (delete_item(fname, st.st_mode, del_opts) != 0)
			return;
		statret = -1;
		stat_errno = ENOENT;
	}

	if (statret != 0 && basis_dir[0] != NULL) {
		int j = try_dests_reg(file, fname, ndx, fnamecmpbuf, &st,
				      itemizing, maybe_ATTRS_REPORT, code);
		if (j == -2)
			return;
		if (j != -1) {
			fnamecmp = fnamecmpbuf;
			fnamecmp_type = j;
			statret = 0;
		}
	}

	real_ret = statret;
	real_st = st;

	if (partial_dir && (partialptr = partial_dir_fname(fname)) != NULL
	    && link_stat(partialptr, &partial_st, 0) == 0
	    && S_ISREG(partial_st.st_mode)) {
		if (statret != 0)
			goto prepare_to_open;
	} else
		partialptr = NULL;

	if (statret != 0 && fuzzy_dirlist && dry_run <= 1) {
		int j = find_fuzzy(file, fuzzy_dirlist);
		if (j >= 0) {
			fuzzy_file = fuzzy_dirlist->files[j];
			f_name(fuzzy_file, fnamecmpbuf);
			if (verbose > 2) {
				rprintf(FINFO, "fuzzy basis selected for %s: %s\n",
					fname, fnamecmpbuf);
			}
			st.st_size = fuzzy_file->length;
			statret = 0;
			fnamecmp = fnamecmpbuf;
			fnamecmp_type = FNAMECMP_FUZZY;
		}
	}

	if (statret != 0) {
		if (preserve_hard_links && file->link_u.links
		    && hard_link_check(file, ndx, fname, statret, &st,
				       itemizing, code, HL_SKIP))
			return;
		if (stat_errno == ENOENT)
			goto notify_others;
		rsyserr(FERROR, stat_errno, "recv_generator: failed to stat %s",
			full_fname(fname));
		return;
	}

	if (append_mode && st.st_size > file->length)
		return;

	if (fnamecmp_type <= FNAMECMP_BASIS_DIR_HIGH)
		;
	else if (fnamecmp_type == FNAMECMP_FUZZY)
		;
	else if (unchanged_file(fnamecmp, file, &st)) {
		if (partialptr) {
			do_unlink(partialptr);
			handle_partial_dir(partialptr, PDIR_DELETE);
		}
		if (itemizing) {
			itemize(file, ndx, real_ret, &real_st,
				0, 0, NULL);
		}
		set_file_attrs(fname, file, &st, maybe_ATTRS_REPORT);
		if (preserve_hard_links && file->link_u.links)
			hard_link_cluster(file, ndx, itemizing, code);
		return;
	}

  prepare_to_open:
	if (partialptr) {
		st = partial_st;
		fnamecmp = partialptr;
		fnamecmp_type = FNAMECMP_PARTIAL_DIR;
		statret = 0;
	}

	if (!do_xfers || read_batch || whole_file)
		goto notify_others;

	if (fuzzy_dirlist) {
		int j = flist_find(fuzzy_dirlist, file);
		if (j >= 0) /* don't use changing file as future fuzzy basis */
			fuzzy_dirlist->files[j]->flags |= FLAG_NO_FUZZY;
	}

	/* open the file */
	fd = do_open(fnamecmp, O_RDONLY, 0);

	if (fd == -1) {
		rsyserr(FERROR, errno, "failed to open %s, continuing",
			full_fname(fnamecmp));
	  pretend_missing:
		/* pretend the file didn't exist */
		if (preserve_hard_links && file->link_u.links
		    && hard_link_check(file, ndx, fname, statret, &st,
				       itemizing, code, HL_SKIP))
			return;
		statret = real_ret = -1;
		goto notify_others;
	}

	if (inplace && make_backups && fnamecmp_type == FNAMECMP_FNAME) {
		if (!(backupptr = get_backup_name(fname))) {
			close(fd);
			return;
		}
		if (!(back_file = make_file(fname, NULL, NULL, 0, NO_FILTERS))) {
			close(fd);
			goto pretend_missing;
		}
		if (robust_unlink(backupptr) && errno != ENOENT) {
			rsyserr(FERROR, errno, "unlink %s",
				full_fname(backupptr));
			free(back_file);
			close(fd);
			return;
		}
		if ((f_copy = do_open(backupptr,
		    O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0600)) < 0) {
			rsyserr(FERROR, errno, "open %s",
				full_fname(backupptr));
			free(back_file);
			close(fd);
			return;
		}
		fnamecmp_type = FNAMECMP_BACKUP;
	}

	if (verbose > 3) {
		rprintf(FINFO, "gen mapped %s of size %.0f\n",
			fnamecmp, (double)st.st_size);
	}

	if (verbose > 2)
		rprintf(FINFO, "generating and sending sums for %d\n", ndx);

  notify_others:
	if (remove_sent_files && !delay_updates && !phase)
	    increment_active_files(ndx, itemizing, code);
	write_int(f_out, ndx);
	if (itemizing) {
		int iflags = ITEM_TRANSFER;
		if (always_checksum)
			iflags |= ITEM_REPORT_CHECKSUM;
		if (fnamecmp_type != FNAMECMP_FNAME)
			iflags |= ITEM_BASIS_TYPE_FOLLOWS;
		if (fnamecmp_type == FNAMECMP_FUZZY)
			iflags |= ITEM_XNAME_FOLLOWS;
		itemize(file, -1, real_ret, &real_st, iflags, fnamecmp_type,
			fuzzy_file ? fuzzy_file->basename : NULL);
	}

	if (!do_xfers) {
		if (preserve_hard_links && file->link_u.links)
			hard_link_cluster(file, ndx, itemizing, code);
		return;
	}
	if (read_batch)
		return;

	if (statret != 0 || whole_file) {
		write_sum_head(f_out, NULL);
		return;
	}

	generate_and_send_sums(fd, st.st_size, f_out, f_copy);

	if (f_copy >= 0) {
		close(f_copy);
		set_file_attrs(backupptr, back_file, NULL, 0);
		if (verbose > 1) {
			rprintf(FINFO, "backed up %s to %s\n",
				fname, backupptr);
		}
		free(back_file);
	}

	close(fd);
}