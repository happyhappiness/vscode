void send_files(struct file_list *flist, int f_out, int f_in)
{
	int fd = -1;
	struct sum_struct *s;
	struct map_struct *mbuf = NULL;
	STRUCT_STAT st;
	char *fname2, fname[MAXPATHLEN];
	char xname[MAXPATHLEN];
	uchar fnamecmp_type;
	int iflags, xlen;
	struct file_struct *file;
	int phase = 0, max_phase = protocol_version >= 29 ? 2 : 1;
	struct stats initial_stats;
	int save_make_backups = make_backups;
	int itemizing = am_daemon ? daemon_log_format_has_i
		      : !am_server && log_format_has_i;
	int f_xfer = write_batch < 0 ? batch_fd : f_out;
	int i, j;

	if (verbose > 2)
		rprintf(FINFO, "send_files starting\n");

	while (1) {
		unsigned int offset;

		i = read_int(f_in);
		if (i == -1) {
			if (++phase > max_phase)
				break;
			csum_length = SUM_LENGTH;
			if (verbose > 2)
				rprintf(FINFO, "send_files phase=%d\n", phase);
			write_int(f_out, -1);
			/* For inplace: redo phase turns off the backup
			 * flag so that we do a regular inplace send. */
			make_backups = 0;
			continue;
		}

		iflags = read_item_attrs(f_in, f_out, i, &fnamecmp_type,
					 xname, &xlen);
		if (iflags == ITEM_IS_NEW) /* no-op packet */
			continue;

		file = flist->files[i];
		if (file->dir.root) {
			/* N.B. We're sure that this fits, so offset is OK. */
			offset = strlcpy(fname, file->dir.root, sizeof fname);
			if (!offset || fname[offset-1] != '/')
				fname[offset++] = '/';
		} else
			offset = 0;
		fname2 = f_name_to(file, fname + offset);

		if (verbose > 2)
			rprintf(FINFO, "send_files(%d, %s)\n", i, fname);

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

		updating_basis_file = inplace && (protocol_version >= 29
			? fnamecmp_type == FNAMECMP_FNAME : !make_backups);

		stats.current_file_index = i;
		stats.num_transferred_files++;
		stats.total_transferred_size += file->length;

		if (!do_xfers) { /* log the transfer */
			if (!am_server && log_format)
				log_item(file, &stats, iflags, NULL);
			write_ndx_and_attrs(f_out, i, iflags, fnamecmp_type,
					    xname, xlen);
			continue;
		}

		initial_stats = stats;

		if (!(s = receive_sums(f_in))) {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR, "receive_sums failed\n");
			return;
		}

		fd = do_open(fname, O_RDONLY, 0);
		if (fd == -1) {
			if (errno == ENOENT) {
				enum logcode c = am_daemon
				    && protocol_version < 28 ? FERROR
							     : FINFO;
				io_error |= IOERR_VANISHED;
				rprintf(c, "file has vanished: %s\n",
					full_fname(fname));
			} else {
				io_error |= IOERR_GENERAL;
				rsyserr(FERROR, errno,
					"send_files failed to open %s",
					full_fname(fname));
			}
			free_sums(s);
			continue;
		}

		/* map the local file */
		if (do_fstat(fd, &st) != 0) {
			io_error |= IOERR_GENERAL;
			rsyserr(FERROR, errno, "fstat failed");
			free_sums(s);
			close(fd);
			return;
		}

		if (st.st_size) {
			int32 read_size = MAX(s->blength * 3, MAX_MAP_SIZE);
			mbuf = map_file(fd, st.st_size, read_size, s->blength);
		} else
			mbuf = NULL;

		if (verbose > 2) {
			rprintf(FINFO, "send_files mapped %s of size %.0f\n",
				safe_fname(fname), (double)st.st_size);
		}

		write_ndx_and_attrs(f_out, i, iflags, fnamecmp_type,
				    xname, xlen);
		write_sum_head(f_xfer, s);

		if (verbose > 2) {
			rprintf(FINFO, "calling match_sums %s\n",
				safe_fname(fname));
		}

		if (log_before_transfer)
			log_item(file, &initial_stats, iflags, NULL);
		else if (!am_server && verbose && do_progress)
			rprintf(FINFO, "%s\n", safe_fname(fname2));

		set_compression(fname);

		match_sums(f_xfer, s, mbuf, st.st_size);
		if (do_progress)
			end_progress(st.st_size);

		if (!log_before_transfer)
			log_item(file, &initial_stats, iflags, NULL);

		if (mbuf) {
			j = unmap_file(mbuf);
			if (j) {
				io_error |= IOERR_GENERAL;
				rsyserr(FERROR, j,
					"read errors mapping %s",
					full_fname(fname));
			}
		}
		close(fd);

		free_sums(s);

		if (verbose > 2) {
			rprintf(FINFO, "sender finished %s\n",
				safe_fname(fname));
		}

		/* Flag that we actually sent this entry. */
		file->flags |= FLAG_SENT;
	}
	make_backups = save_make_backups;

	if (verbose > 2)
		rprintf(FINFO, "send files finished\n");

	match_report();

	write_int(f_out, -1);
}