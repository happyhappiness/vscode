int recv_files(int f_in, struct file_list *flist, char *local_name)
{
	int next_gen_i = -1;
	int fd1,fd2;
	STRUCT_STAT st;
	int iflags, xlen;
	char *fname, fbuf[MAXPATHLEN];
	char xname[MAXPATHLEN];
	char fnametmp[MAXPATHLEN];
	char *fnamecmp, *partialptr, numbuf[4];
	char fnamecmpbuf[MAXPATHLEN];
	uchar fnamecmp_type;
	struct file_struct *file;
	struct stats initial_stats;
	int save_make_backups = make_backups;
	int itemizing = am_daemon ? daemon_log_format_has_i
		      : !am_server && log_format_has_i;
	int max_phase = protocol_version >= 29 ? 2 : 1;
	int i, recv_ok;

	if (verbose > 2)
		rprintf(FINFO,"recv_files(%d) starting\n",flist->count);

	if (flist->hlink_pool) {
		pool_destroy(flist->hlink_pool);
		flist->hlink_pool = NULL;
	}

	if (delay_updates)
		init_delayed_bits(flist->count);

	while (1) {
		cleanup_disable();

		i = read_int(f_in);
		if (i == -1) {
			if (read_batch) {
				get_next_gen_i(batch_gen_fd, next_gen_i,
					       flist->count);
				next_gen_i = -1;
			}
			if (++phase > max_phase)
				break;
			csum_length = SUM_LENGTH;
			if (verbose > 2)
				rprintf(FINFO, "recv_files phase=%d\n", phase);
			if (phase == 2 && delay_updates)
				handle_delayed_updates(flist, local_name);
			send_msg(MSG_DONE, "", 0);
			if (keep_partial && !partial_dir)
				make_backups = 0; /* prevents double backup */
			continue;
		}

		iflags = read_item_attrs(f_in, -1, i, &fnamecmp_type,
					 xname, &xlen);
		if (iflags == ITEM_IS_NEW) /* no-op packet */
			continue;

		file = flist->files[i];
		fname = local_name ? local_name : f_name_to(file, fbuf);

		if (verbose > 2)
			rprintf(FINFO, "recv_files(%s)\n", safe_fname(fname));

		if (!(iflags & ITEM_TRANSFER)) {
			maybe_log_item(file, iflags, itemizing, xname);
			continue;
		}
		if (phase == 2) {
			rprintf(FERROR,
				"got transfer request in phase 2 [%s]\n",
				who_am_i());
			exit_cleanup(RERR_PROTOCOL);
		}

		stats.current_file_index = i;
		stats.num_transferred_files++;
		stats.total_transferred_size += file->length;
		cleanup_got_literal = 0;

		if (server_filter_list.head
		    && check_filter(&server_filter_list, fname, 0) < 0) {
			rprintf(FERROR, "attempt to hack rsync failed.\n");
			exit_cleanup(RERR_PROTOCOL);
		}

		if (!do_xfers) { /* log the transfer */
			if (!am_server && log_format)
				log_item(file, &stats, iflags, NULL);
			if (read_batch)
				discard_receive_data(f_in, file->length);
			continue;
		}
		if (write_batch < 0) {
			log_item(file, &stats, iflags, NULL);
			if (!am_server)
				discard_receive_data(f_in, file->length);
			continue;
		}

		if (read_batch) {
			next_gen_i = get_next_gen_i(batch_gen_fd, next_gen_i, i);
			if (i < next_gen_i) {
				rprintf(FINFO, "(Skipping batched update for \"%s\")\n",
					safe_fname(fname));
				discard_receive_data(f_in, file->length);
				continue;
			}
			next_gen_i = -1;
		}

		partialptr = partial_dir ? partial_dir_fname(fname) : fname;

		if (protocol_version >= 29) {
			switch (fnamecmp_type) {
			case FNAMECMP_FNAME:
				fnamecmp = fname;
				break;
			case FNAMECMP_PARTIAL_DIR:
				fnamecmp = partialptr;
				break;
			case FNAMECMP_BACKUP:
				fnamecmp = get_backup_name(fname);
				break;
			case FNAMECMP_FUZZY:
				if (file->dirname) {
					pathjoin(fnamecmpbuf, MAXPATHLEN,
						 file->dirname, xname);
					fnamecmp = fnamecmpbuf;
				} else
					fnamecmp = xname;
				break;
			default:
				if (fnamecmp_type >= basis_dir_cnt) {
					rprintf(FERROR,
						"invalid basis_dir index: %d.\n",
						fnamecmp_type);
					exit_cleanup(RERR_PROTOCOL);
				}
				pathjoin(fnamecmpbuf, sizeof fnamecmpbuf,
					 basis_dir[fnamecmp_type], fname);
				fnamecmp = fnamecmpbuf;
				break;
			}
			if (!fnamecmp || (server_filter_list.head
			  && check_filter(&server_filter_list, fname, 0) < 0))
				fnamecmp = fname;
		} else {
			/* Reminder: --inplace && --partial-dir are never
			 * enabled at the same time. */
			if (inplace && make_backups) {
				if (!(fnamecmp = get_backup_name(fname)))
					fnamecmp = fname;
			} else if (partial_dir && partialptr)
				fnamecmp = partialptr;
			else
				fnamecmp = fname;
		}

		initial_stats = stats;

		/* open the file */
		fd1 = do_open(fnamecmp, O_RDONLY, 0);

		if (fd1 == -1 && protocol_version < 29) {
			if (fnamecmp != fname) {
				fnamecmp = fname;
				fd1 = do_open(fnamecmp, O_RDONLY, 0);
			}

			if (fd1 == -1 && basis_dir[0]) {
				/* pre-29 allowed only one alternate basis */
				pathjoin(fnamecmpbuf, sizeof fnamecmpbuf,
					 basis_dir[0], fname);
				fnamecmp = fnamecmpbuf;
				fd1 = do_open(fnamecmp, O_RDONLY, 0);
			}
		}

		if (fd1 != -1 && do_fstat(fd1,&st) != 0) {
			rsyserr(FERROR, errno, "fstat %s failed",
				full_fname(fnamecmp));
			discard_receive_data(f_in, file->length);
			close(fd1);
			continue;
		}

		if (fd1 != -1 && S_ISDIR(st.st_mode) && fnamecmp == fname) {
			/* this special handling for directories
			 * wouldn't be necessary if robust_rename()
			 * and the underlying robust_unlink could cope
			 * with directories
			 */
			rprintf(FERROR,"recv_files: %s is a directory\n",
				full_fname(fnamecmp));
			discard_receive_data(f_in, file->length);
			close(fd1);
			continue;
		}

		if (fd1 != -1 && !S_ISREG(st.st_mode)) {
			close(fd1);
			fd1 = -1;
		}

		if (fd1 != -1 && !preserve_perms) {
			/* if the file exists already and we aren't preserving
			 * permissions then act as though the remote end sent
			 * us the file permissions we already have */
			file->mode = st.st_mode;
		}

		/* We now check to see if we are writing file "inplace" */
		if (inplace)  {
			fd2 = do_open(fname, O_WRONLY|O_CREAT, 0);
			if (fd2 == -1) {
				rsyserr(FERROR, errno, "open %s failed",
					full_fname(fname));
				discard_receive_data(f_in, file->length);
				if (fd1 != -1)
					close(fd1);
				continue;
			}
		} else {
			if (!get_tmpname(fnametmp,fname)) {
				discard_receive_data(f_in, file->length);
				if (fd1 != -1)
					close(fd1);
				continue;
			}

			/* we initially set the perms without the
			 * setuid/setgid bits to ensure that there is no race
			 * condition. They are then correctly updated after
			 * the lchown. Thanks to snabb@epipe.fi for pointing
			 * this out.  We also set it initially without group
			 * access because of a similar race condition. */
			fd2 = do_mkstemp(fnametmp, file->mode & INITACCESSPERMS);

			/* in most cases parent directories will already exist
			 * because their information should have been previously
			 * transferred, but that may not be the case with -R */
			if (fd2 == -1 && relative_paths && errno == ENOENT
			    && create_directory_path(fnametmp, orig_umask) == 0) {
				/* Get back to name with XXXXXX in it. */
				get_tmpname(fnametmp, fname);
				fd2 = do_mkstemp(fnametmp, file->mode & INITACCESSPERMS);
			}
			if (fd2 == -1) {
				rsyserr(FERROR, errno, "mkstemp %s failed",
					full_fname(fnametmp));
				discard_receive_data(f_in, file->length);
				if (fd1 != -1)
					close(fd1);
				continue;
			}

			if (partialptr)
				cleanup_set(fnametmp, partialptr, file, fd1, fd2);
		}

		/* log the transfer */
		if (log_before_transfer)
			log_item(file, &initial_stats, iflags, NULL);
		else if (!am_server && verbose && do_progress)
			rprintf(FINFO, "%s\n", safe_fname(fname));

		/* recv file data */
		recv_ok = receive_data(f_in, fnamecmp, fd1, st.st_size,
				       fname, fd2, file->length);

		if (!log_before_transfer)
			log_item(file, &initial_stats, iflags, NULL);

		if (fd1 != -1)
			close(fd1);
		if (close(fd2) < 0) {
			rsyserr(FERROR, errno, "close failed on %s",
				full_fname(fnametmp));
			exit_cleanup(RERR_FILEIO);
		}

		if ((recv_ok && (!delay_updates || !partialptr)) || inplace) {
			finish_transfer(fname, fnametmp, file, recv_ok, 1);
			if (partialptr != fname && fnamecmp == partialptr) {
				do_unlink(partialptr);
				handle_partial_dir(partialptr, PDIR_DELETE);
			}
		} else if (keep_partial && partialptr
		    && handle_partial_dir(partialptr, PDIR_CREATE)) {
			finish_transfer(partialptr, fnametmp, file, recv_ok,
					!partial_dir);
			if (delay_updates && recv_ok) {
				set_delayed_bit(i);
				recv_ok = -1;
			}
		} else {
			partialptr = NULL;
			do_unlink(fnametmp);
		}

		cleanup_disable();

		if (recv_ok > 0) {
			if (remove_sent_files
			    || (preserve_hard_links && file->link_u.links)) {
				SIVAL(numbuf, 0, i);
				send_msg(MSG_SUCCESS, numbuf, 4);
			}
		} else if (!recv_ok) {
			int msgtype = phase || read_batch ? FERROR : FINFO;
			if (msgtype == FERROR || verbose) {
				char *errstr, *redostr, *keptstr;
				if (!(keep_partial && partialptr) && !inplace)
					keptstr = "discarded";
				else if (partial_dir)
					keptstr = "put into partial-dir";
				else
					keptstr = "retained";
				if (msgtype == FERROR) {
					errstr = "ERROR";
					redostr = "";
				} else {
					errstr = "WARNING";
					redostr = " (will try again)";
				}
				rprintf(msgtype,
					"%s: %s failed verification -- update %s%s.\n",
					errstr, safe_fname(fname),
					keptstr, redostr);
			}
			if (!phase) {
				SIVAL(numbuf, 0, i);
				send_msg(MSG_REDO, numbuf, 4);
			}
		}
	}
	make_backups = save_make_backups;

	if (phase == 2 && delay_updates) /* for protocol_version < 29 */
		handle_delayed_updates(flist, local_name);

	if (verbose > 2)
		rprintf(FINFO,"recv_files finished\n");

	return 0;
}