static void recv_generator(char *fname, struct file_struct *file, int ndx,
			   int itemizing, int maybe_PERMS_REPORT,
			   enum logcode code, int f_out)
{
	static int missing_below = -1, excluded_below = -1;
	static char *fuzzy_dirname = "";
	static struct file_list *fuzzy_dirlist = NULL;
	struct file_struct *fuzzy_file = NULL;
	int fd = -1, f_copy = -1;
	STRUCT_STAT st, real_st, partial_st;
	struct file_struct *back_file = NULL;
	int statret, real_ret, stat_errno;
	char *fnamecmp, *partialptr, *backupptr = NULL;
	char fnamecmpbuf[MAXPATHLEN];
	uchar fnamecmp_type;

	if (list_only)
		return;

	if (!fname) {
		if (fuzzy_dirlist) {
			flist_free(fuzzy_dirlist);
			fuzzy_dirlist = NULL;
			fuzzy_dirname = "";
		}
		if (missing_below >= 0) {
			dry_run--;
			missing_below = -1;
		}
		return;
	}

	if (verbose > 2) {
		rprintf(FINFO, "recv_generator(%s,%d)\n",
			safe_fname(fname), ndx);
	}

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
					safe_fname(fname));
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
		if (fuzzy_basis && S_ISREG(file->mode)) {
			char *dn = file->dirname ? file->dirname : ".";
			if (fuzzy_dirname != dn
			    && strcmp(fuzzy_dirname, dn) != 0) {
				if (fuzzy_dirlist)
					flist_free(fuzzy_dirlist);
				fuzzy_dirlist = get_dirlist(dn, -1, 1);
			}
			fuzzy_dirname = dn;
		}

		statret = link_stat(fname, &st,
				    keep_dirlinks && S_ISDIR(file->mode));
		stat_errno = errno;
	}

	if (only_existing && statret == -1 && stat_errno == ENOENT) {
		/* we only want to update existing files */
		if (verbose > 1) {
			rprintf(FINFO, "not creating new %s \"%s\"\n",
				S_ISDIR(file->mode) ? "directory" : "file",
				safe_fname(fname));
		}
		return;
	}

	if (statret == 0 && !preserve_perms
	    && S_ISDIR(st.st_mode) == S_ISDIR(file->mode)) {
		/* if the file exists already and we aren't perserving
		 * permissions then act as though the remote end sent
		 * us the file permissions we already have */
		file->mode = (file->mode & ~CHMOD_BITS)
			   | (st.st_mode & CHMOD_BITS);
	}

	if (S_ISDIR(file->mode)) {
		/* The file to be received is a directory, so we need
		 * to prepare appropriately.  If there is already a
		 * file of that name and it is *not* a directory, then
		 * we need to delete it.  If it doesn't exist, then
		 * (perhaps recursively) create it. */
		if (statret == 0 && !S_ISDIR(st.st_mode)) {
			if (delete_item(fname, st.st_mode, DEL_TERSE) < 0)
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
		if (statret != 0 && do_mkdir(fname,file->mode) != 0 && errno != EEXIST) {
			if (!relative_paths || errno != ENOENT
			    || create_directory_path(fname, orig_umask) < 0
			    || (do_mkdir(fname, file->mode) < 0 && errno != EEXIST)) {
				rsyserr(FERROR, errno,
					"recv_generator: mkdir %s failed",
					full_fname(fname));
			}
		}
		if (set_perms(fname, file, statret ? NULL : &st, 0)
		    && verbose && code && f_out != -1)
			rprintf(code, "%s/\n", safe_fname(fname));
		if (delete_during && f_out != -1 && !phase && dry_run < 2
		    && (file->flags & FLAG_DEL_HERE))
			delete_in_dir(the_file_list, fname, file);
		return;
	}

	if (preserve_links && S_ISLNK(file->mode)) {
#ifdef SUPPORT_LINKS
		if (safe_symlinks && unsafe_symlink(file->u.link, fname)) {
			if (verbose) {
				if (the_file_list->count == 1)
					fname = f_name(file);
				rprintf(FINFO,
					"ignoring unsafe symlink %s -> \"%s\"\n",
					full_fname(fname),
					safe_fname(file->u.link));
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
					set_perms(fname, file, &st,
						  maybe_PERMS_REPORT);
					return;
				}
			}
			/* Not the right symlink (or not a symlink), so
			 * delete it. */
			if (delete_item(fname, st.st_mode, DEL_TERSE) < 0)
				return;
			if (!S_ISLNK(st.st_mode))
				statret = -1;
		}
		if (do_symlink(file->u.link,fname) != 0) {
			rsyserr(FERROR, errno, "symlink %s -> \"%s\" failed",
				full_fname(fname), safe_fname(file->u.link));
		} else {
			set_perms(fname,file,NULL,0);
			if (itemizing) {
				itemize(file, ndx, statret, &st,
					ITEM_LOCAL_CHANGE, 0, NULL);
			}
			if (code && verbose) {
				rprintf(code, "%s -> %s\n", safe_fname(fname),
					safe_fname(file->u.link));
			}
			if (remove_sent_files && !dry_run) {
				char numbuf[4];
				SIVAL(numbuf, 0, ndx);
				send_msg(MSG_SUCCESS, numbuf, 4);
			}
		}
#endif
		return;
	}

	if (am_root && preserve_devices && IS_DEVICE(file->mode)) {
		if (statret != 0 ||
		    st.st_mode != file->mode ||
		    st.st_rdev != file->u.rdev) {
			if (delete_item(fname, st.st_mode, DEL_TERSE) < 0)
				return;
			if (!IS_DEVICE(st.st_mode))
				statret = -1;
			if (verbose > 2) {
				rprintf(FINFO,"mknod(%s,0%o,0x%x)\n",
					safe_fname(fname),
					(int)file->mode, (int)file->u.rdev);
			}
			if (do_mknod(fname,file->mode,file->u.rdev) != 0) {
				rsyserr(FERROR, errno, "mknod %s failed",
					full_fname(fname));
			} else {
				set_perms(fname,file,NULL,0);
				if (itemizing) {
					itemize(file, ndx, statret, &st,
						ITEM_LOCAL_CHANGE, 0, NULL);
				}
				if (code && verbose) {
					rprintf(code, "%s\n",
						safe_fname(fname));
				}
			}
		} else {
			if (itemizing)
				itemize(file, ndx, statret, &st, 0, 0, NULL);
			set_perms(fname, file, &st, maybe_PERMS_REPORT);
		}
		return;
	}

	if (preserve_hard_links
	    && hard_link_check(file, ndx, fname, statret, &st,
			       itemizing, code, HL_CHECK_MASTER))
		return;

	if (!S_ISREG(file->mode)) {
		if (the_file_list->count == 1)
			fname = f_name(file);
		rprintf(FINFO, "skipping non-regular file \"%s\"\n",
			safe_fname(fname));
		return;
	}

	if (max_size && file->length > max_size) {
		if (verbose > 1) {
			if (the_file_list->count == 1)
				fname = f_name(file);
			rprintf(FINFO, "%s is over max-size\n",
				safe_fname(fname));
		}
		return;
	}

	if (opt_ignore_existing && statret == 0) {
		if (verbose > 1)
			rprintf(FINFO, "%s exists\n", safe_fname(fname));
		return;
	}

	if (update_only && statret == 0
	    && cmp_modtime(st.st_mtime, file->modtime) > 0) {
		if (verbose > 1)
			rprintf(FINFO, "%s is newer\n", safe_fname(fname));
		return;
	}

	fnamecmp = fname;
	fnamecmp_type = FNAMECMP_FNAME;

	if (statret == 0 && !S_ISREG(st.st_mode)) {
		if (delete_item(fname, st.st_mode, DEL_TERSE) != 0)
			return;
		statret = -1;
		stat_errno = ENOENT;
	}

	if (statret != 0 && basis_dir[0] != NULL) {
		int best_match = -1;
		int match_level = 0;
		int i = 0;
		do {
			pathjoin(fnamecmpbuf, sizeof fnamecmpbuf,
				 basis_dir[i], fname);
			if (link_stat(fnamecmpbuf, &st, 0) < 0
			    || !S_ISREG(st.st_mode))
				continue;
			switch (match_level) {
			case 0:
				best_match = i;
				match_level = 1;
				/* FALL THROUGH */
			case 1:
				if (!unchanged_file(fnamecmpbuf, file, &st))
					continue;
				best_match = i;
				match_level = 2;
				if (copy_dest)
					break;
				/* FALL THROUGH */
			case 2:
				if (!unchanged_attrs(file, &st))
					continue;
				best_match = i;
				match_level = 3;
				break;
			}
			break;
		} while (basis_dir[++i] != NULL);
		if (match_level) {
			statret = 0;
			if (i != best_match) {
				i = best_match;
				pathjoin(fnamecmpbuf, sizeof fnamecmpbuf,
					 basis_dir[i], fname);
				if (link_stat(fnamecmpbuf, &st, 0) < 0) {
					match_level = 0;
					statret = -1;
					stat_errno = errno;
				}
			}
#ifdef HAVE_LINK
			if (link_dest && match_level == 3) {
				if (hard_link_one(file, ndx, fname, -1, &st,
						  fnamecmpbuf, 1,
						  itemizing && verbose > 1,
						  code) == 0) {
					if (preserve_hard_links
					    && file->link_u.links) {
						hard_link_cluster(file, ndx,
								  itemizing,
								  code);
					}
					return;
				}
				match_level = 2;
			}
#endif
			if (match_level == 2) {
				/* Copy the file locally. */
				if (copy_file(fnamecmpbuf, fname, file->mode) < 0) {
					if (verbose) {
						rsyserr(FINFO, errno,
							"copy_file %s => %s",
							full_fname(fnamecmpbuf),
							safe_fname(fname));
					}
					match_level = 0;
					statret = -1;
				} else {
					if (itemizing) {
						itemize(file, ndx, 0, &st,
							ITEM_LOCAL_CHANGE, 0,
							NULL);
					} else if (verbose && code) {
						rprintf(code, "%s\n",
							safe_fname(fname));
					}
					set_perms(fname, file, NULL,
						  maybe_PERMS_REPORT);
					if (preserve_hard_links
					    && file->link_u.links) {
						hard_link_cluster(file, ndx,
								  itemizing,
								  code);
					}
					return;
				}
			} else if (compare_dest || match_level == 1) {
				fnamecmp = fnamecmpbuf;
				fnamecmp_type = i;
			}
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

	if (statret != 0 && fuzzy_basis && dry_run <= 1) {
		int j = find_fuzzy(file, fuzzy_dirlist);
		if (j >= 0) {
			fuzzy_file = fuzzy_dirlist->files[j];
			f_name_to(fuzzy_file, fnamecmpbuf);
			if (verbose > 2) {
				rprintf(FINFO, "fuzzy basis selected for %s: %s\n",
					safe_fname(fname), safe_fname(fnamecmpbuf));
			}
			st.st_size = fuzzy_file->length;
			statret = 0;
			fnamecmp = fnamecmpbuf;
			fnamecmp_type = FNAMECMP_FUZZY;
		}
	}

	if (statret != 0) {
		if (preserve_hard_links
		    && hard_link_check(file, ndx, fname, statret, &st,
				       itemizing, code, HL_SKIP))
			return;
		if (stat_errno == ENOENT)
			goto notify_others;
		if (verbose > 1) {
			rsyserr(FERROR, stat_errno,
				"recv_generator: failed to stat %s",
				full_fname(fname));
		}
		return;
	}

	if (!compare_dest && fnamecmp_type <= FNAMECMP_BASIS_DIR_HIGH)
		;
	else if (fnamecmp_type == FNAMECMP_FUZZY)
		;
	else if (unchanged_file(fnamecmp, file, &st)) {
		if (fnamecmp_type == FNAMECMP_FNAME) {
			if (itemizing) {
				itemize(file, ndx, real_ret, &real_st,
					0, 0, NULL);
			}
			set_perms(fname, file, &st, maybe_PERMS_REPORT);
			if (preserve_hard_links && file->link_u.links)
				hard_link_cluster(file, ndx, itemizing, code);
			return;
		}
		/* Only --compare-dest gets here. */
		itemize(file, ndx, real_ret, &real_st,
			ITEM_NO_DEST_AND_NO_UPDATE, 0, NULL);
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

	if (fuzzy_basis) {
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
		if (preserve_hard_links
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
		if (!(back_file = make_file(fname, NULL, NO_FILTERS))) {
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
			safe_fname(fnamecmp), (double)st.st_size);
	}

	if (verbose > 2)
		rprintf(FINFO, "generating and sending sums for %d\n", ndx);

notify_others:
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
		set_perms(backupptr, back_file, NULL, 0);
		if (verbose > 1) {
			rprintf(FINFO, "backed up %s to %s\n",
				safe_fname(fname), safe_fname(backupptr));
		}
		free(back_file);
	}

	close(fd);
}