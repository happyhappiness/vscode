void send_files(struct file_list *flist, int f_out, int f_in)
{
	int fd = -1;
	struct sum_struct *s;
	struct map_struct *buf = NULL;
	STRUCT_STAT st;
	char fname[MAXPATHLEN];
	int i;
	struct file_struct *file;
	int phase = 0;
	extern struct stats stats;
	struct stats initial_stats;
	extern int write_batch;   /* dw */
	extern int read_batch;    /* dw */
	int checksums_match;   /* dw */
	int buff_len;  /* dw */
	char buff[CHUNK_SIZE];    /* dw */
	int j;   /* dw */
	int done;   /* dw */

	if (verbose > 2)
		rprintf(FINFO, "send_files starting\n");

	while (1) {
		int offset = 0;

		i = read_int(f_in);
		if (i == -1) {
			if (phase == 0) {
				phase++;
				csum_length = SUM_LENGTH;
				write_int(f_out, -1);
				if (verbose > 2)
					rprintf(FINFO, "send_files phase=%d\n", phase);
				continue;
			}
			break;
		}

		if (i < 0 || i >= flist->count) {
			rprintf(FERROR, "Invalid file index %d (count=%d)\n",
				i, flist->count);
			exit_cleanup(RERR_PROTOCOL);
		}

		file = flist->files[i];

		stats.num_transferred_files++;
		stats.total_transferred_size += file->length;

		fname[0] = 0;
		if (file->basedir) {
			strlcpy(fname, file->basedir, MAXPATHLEN);
			if (strlen(fname) == MAXPATHLEN-1) {
				io_error |= IOERR_GENERAL;
				rprintf(FERROR, "send_files failed on long-named directory %s\n",
					full_fname(fname));
				return;
			}
			strlcat(fname, "/", MAXPATHLEN);
			offset = strlen(file->basedir)+1;
		}
		strlcat(fname, f_name(file), MAXPATHLEN);

		if (verbose > 2)
			rprintf(FINFO, "send_files(%d, %s)\n", i, fname);

		if (dry_run) {
			if (!am_server && verbose) {	/* log transfer */
				rprintf(FINFO, "%s\n", fname+offset);
			}
			write_int(f_out, i);
			continue;
		}

		initial_stats = stats;

		s = receive_sums(f_in);
		if (!s) {
			io_error |= IOERR_GENERAL;
			rprintf(FERROR, "receive_sums failed\n");
			return;
		}

		if (write_batch)
			write_batch_csum_info(&i, flist->count, s);

		if (!read_batch) {
			fd = do_open(fname, O_RDONLY, 0);
			if (fd == -1) {
				if (errno == ENOENT) {
					io_error |= IOERR_VANISHED;
					rprintf(FINFO, "file has vanished: %s\n",
			 			full_fname(fname));
				} else {
					io_error |= IOERR_GENERAL;
					rprintf(FERROR, "send_files failed to open %s: %s\n",
						full_fname(fname), strerror(errno));
				}
				free_sums(s);
				continue;
			}

			/* map the local file */
			if (do_fstat(fd, &st) != 0) {
				io_error |= IOERR_GENERAL;
				rprintf(FERROR, "fstat failed: %s\n", strerror(errno));
				free_sums(s);
				close(fd);
				return;
			}

			if (st.st_size > 0) {
				buf = map_file(fd, st.st_size);
			} else {
				buf = NULL;
			}

			if (verbose > 2)
				rprintf(FINFO, "send_files mapped %s of size %.0f\n",
					fname, (double)st.st_size);

			write_int(f_out, i);

			if (write_batch)
				write_batch_delta_file((char *)&i, sizeof(i));

			write_sum_head(f_out, s);
		}

		if (verbose > 2 && !read_batch)
			rprintf(FINFO, "calling match_sums %s\n", fname);

		if (!am_server && verbose) {	/* log transfer */
			rprintf(FINFO, "%s\n", fname+offset);
		}

		set_compression(fname);

		if (read_batch) { /* dw */
			/* read checksums originally computed on sender side */
			read_batch_csum_info(i, s, &checksums_match);
			if (checksums_match) {
				read_batch_delta_file( (char *) &j, sizeof(int) );
				if (j != i) {    /* if flist index entries don't match*/
					rprintf(FINFO, "index mismatch in send_files\n");
					rprintf(FINFO, "read index = %d flist ndx = %d\n", j, i);
					close_batch_delta_file();
					close_batch_csums_file();
					exit_cleanup(1);
				} else {
					write_int(f_out, j);
					write_sum_head(f_out, s);
					done = 0;
					while (!done) {
						read_batch_delta_file( (char *) &buff_len, sizeof(int) );
						write_int(f_out, buff_len);
						if (buff_len == 0) {
							done = 1;
						} else {
							if (buff_len > 0) {
								read_batch_delta_file(buff, buff_len);
								write_buf(f_out, buff, buff_len);
							}
						}
					}  /* end while  */
					read_batch_delta_file( buff, MD4_SUM_LENGTH);
					write_buf(f_out, buff, MD4_SUM_LENGTH);

				}  /* j=i */
			} else {  /* not checksum match */
				rprintf (FINFO, "readbatch & checksums don't match\n");
				rprintf (FINFO, "filename=%s is being skipped\n", fname);
				continue;
			}
		} else  {
			match_sums(f_out, s, buf, st.st_size);
			log_send(file, &initial_stats);
		}

		if (!read_batch) { /* dw */
			if (buf) {
				j = unmap_file(buf);
				if (j) {
					io_error |= IOERR_GENERAL;
					rprintf(FERROR,
					    "read errors mapping %s: (%d) %s\n",
					    full_fname(fname), j, strerror(j));
				}
			}
			close(fd);
		}

		free_sums(s);

		if (verbose > 2)
			rprintf(FINFO, "sender finished %s\n", fname);
	}

	if (verbose > 2)
		rprintf(FINFO, "send files finished\n");

	match_report();

	write_int(f_out, -1);
	if (write_batch || read_batch) { /* dw */
		close_batch_csums_file();
		close_batch_delta_file();
	}

}