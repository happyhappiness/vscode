void send_files(int f_in, int f_out)
{
	int fd = -1;
	struct sum_struct *s;
	struct map_struct *mbuf = NULL;
	STRUCT_STAT st;
	char fname[MAXPATHLEN], xname[MAXPATHLEN];
	const char *path, *slash;
	uchar fnamecmp_type;
	int iflags, xlen;
	struct file_struct *file;
	int phase = 0, max_phase = protocol_version >= 29 ? 2 : 1;
	struct stats initial_stats;
	int itemizing = am_server ? logfile_format_has_i : stdout_format_has_i;
	enum logcode log_code = log_before_transfer ? FLOG : FINFO;
	int f_xfer = write_batch < 0 ? batch_fd : f_out;
	int ndx, j;

	if (verbose > 2)
		rprintf(FINFO, "send_files starting\n");

	while (1) {
		if (inc_recurse)
			send_extra_file_list(f_out, FILECNT_LOOKAHEAD);

		/* This call also sets cur_flist. */
		ndx = read_ndx_and_attrs(f_in, &iflags, &fnamecmp_type,
					 xname, &xlen);
		if (ndx == NDX_DONE) {
			if (inc_recurse && first_flist) {
				flist_free(first_flist);
				if (first_flist) {
					write_ndx(f_out, NDX_DONE);
					continue;
				}
			}
			if (++phase > max_phase)
				break;
			if (verbose > 2)
				rprintf(FINFO, "send_files phase=%d\n", phase);
			write_ndx(f_out, NDX_DONE);
			continue;
		}

		if (inc_recurse)
			send_extra_file_list(f_out, FILECNT_LOOKAHEAD);

		if (ndx - cur_flist->ndx_start >= 0)
			file = cur_flist->files[ndx - cur_flist->ndx_start];
		else
			file = dir_flist->files[cur_flist->parent_ndx];
		if (F_PATHNAME(file)) {
			path = F_PATHNAME(file);
			slash = "/";
		} else {
			path = slash = "";
		}
		if (!change_pathname(file, NULL, 0))
			continue;
		f_name(file, fname);

		if (verbose > 2)
			rprintf(FINFO, "send_files(%d, %s%s%s)\n", ndx, path,slash,fname);

#ifdef SUPPORT_XATTRS
		if (preserve_xattrs && iflags & ITEM_REPORT_XATTR && !dry_run)
			recv_xattr_request(file, f_in);
#endif

		if (!(iflags & ITEM_TRANSFER)) {
			maybe_log_item(file, iflags, itemizing, xname);
			write_ndx_and_attrs(f_out, ndx, iflags, fname, file,
					    fnamecmp_type, xname, xlen);
			continue;
		}
		if (phase == 2) {
			rprintf(FERROR,
				"got transfer request in phase 2 [%s]\n",
				who_am_i());
			exit_cleanup(RERR_PROTOCOL);
		}

		if (file->flags & FLAG_FILE_SENT) {
			if (csum_length == SHORT_SUM_LENGTH) {
				/* For inplace: redo phase turns off the backup
				 * flag so that we do a regular inplace send. */
				make_backups = -make_backups;
				append_mode = -append_mode;
				csum_length = SUM_LENGTH;
			}
		} else {
			if (csum_length != SHORT_SUM_LENGTH) {
				make_backups = -make_backups;
				append_mode = -append_mode;
				csum_length = SHORT_SUM_LENGTH;
			}
		}

		updating_basis_file = inplace && (protocol_version >= 29
			? fnamecmp_type == FNAMECMP_FNAME : make_backups <= 0);

		if (!am_server && do_progress)
			set_current_file_index(file, ndx);
		stats.num_transferred_files++;
		stats.total_transferred_size += F_LENGTH(file);

		if (!do_xfers) { /* log the transfer */
			log_item(FCLIENT, file, &stats, iflags, NULL);
			write_ndx_and_attrs(f_out, ndx, iflags, fname, file,
					    fnamecmp_type, xname, xlen);
			continue;
		}

		initial_stats = stats;

		if (!(s = receive_sums(f_in))) {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR_XFER, "receive_sums failed\n");
			exit_cleanup(RERR_PROTOCOL);
		}

		fd = do_open(fname, O_RDONLY, 0);
		if (fd == -1) {
			if (errno == ENOENT) {
				enum logcode c = am_daemon
				    && protocol_version < 28 ? FERROR
							     : FWARNING;
				io_error |= IOERR_VANISHED;
				rprintf(c, "file has vanished: %s\n",
					full_fname(fname));
			} else {
				io_error |= IOERR_GENERAL;
				rsyserr(FERROR_XFER, errno,
					"send_files failed to open %s",
					full_fname(fname));
			}
			free_sums(s);
			if (protocol_version >= 30)
				send_msg_int(MSG_NO_SEND, ndx);
			continue;
		}

		/* map the local file */
		if (do_fstat(fd, &st) != 0) {
			io_error |= IOERR_GENERAL;
			rsyserr(FERROR_XFER, errno, "fstat failed");
			free_sums(s);
			close(fd);
			exit_cleanup(RERR_PROTOCOL);
		}

		if (st.st_size) {
			int32 read_size = MAX(s->blength * 3, MAX_MAP_SIZE);
			mbuf = map_file(fd, st.st_size, read_size, s->blength);
		} else
			mbuf = NULL;

		if (verbose > 2) {
			rprintf(FINFO, "send_files mapped %s%s%s of size %.0f\n",
				path,slash,fname, (double)st.st_size);
		}

		write_ndx_and_attrs(f_out, ndx, iflags, fname, file,
				    fnamecmp_type, xname, xlen);
		write_sum_head(f_xfer, s);

		if (verbose > 2)
			rprintf(FINFO, "calling match_sums %s%s%s\n", path,slash,fname);

		if (log_before_transfer)
			log_item(FCLIENT, file, &initial_stats, iflags, NULL);
		else if (!am_server && verbose && do_progress)
			rprintf(FCLIENT, "%s\n", fname);

		set_compression(fname);

		match_sums(f_xfer, s, mbuf, st.st_size);
		if (do_progress)
			end_progress(st.st_size);

		log_item(log_code, file, &initial_stats, iflags, NULL);

		if (mbuf) {
			j = unmap_file(mbuf);
			if (j) {
				io_error |= IOERR_GENERAL;
				rsyserr(FERROR_XFER, j,
					"read errors mapping %s",
					full_fname(fname));
			}
		}
		close(fd);

		free_sums(s);

		if (verbose > 2)
			rprintf(FINFO, "sender finished %s%s%s\n", path,slash,fname);

		/* Flag that we actually sent this entry. */
		file->flags |= FLAG_FILE_SENT;
	}
	if (make_backups < 0)
		make_backups = -make_backups;

	if (verbose > 2)
		rprintf(FINFO, "send files finished\n");

	match_report();

	write_ndx(f_out, NDX_DONE);
}