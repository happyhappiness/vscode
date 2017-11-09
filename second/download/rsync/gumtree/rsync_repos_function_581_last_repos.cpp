static void handle_stats(int f)
{
	endtime = time(NULL);

	/* Cache two stats because the read/write code can change it. */
	total_read = stats.total_read;
	total_written = stats.total_written;

	if (INFO_GTE(STATS, 3)) {
		/* These come out from every process */
		show_malloc_stats();
		show_flist_stats();
	}

	if (am_generator)
		return;

	if (am_daemon) {
		if (f == -1 || !am_sender)
			return;
	}

	if (am_server) {
		if (am_sender) {
			write_varlong30(f, total_read, 3);
			write_varlong30(f, total_written, 3);
			write_varlong30(f, stats.total_size, 3);
			if (protocol_version >= 29) {
				write_varlong30(f, stats.flist_buildtime, 3);
				write_varlong30(f, stats.flist_xfertime, 3);
			}
		}
		return;
	}

	/* this is the client */

	if (f < 0 && !am_sender) /* e.g. when we got an empty file list. */
		;
	else if (!am_sender) {
		/* Read the first two in opposite order because the meaning of
		 * read/write swaps when switching from sender to receiver. */
		total_written = read_varlong30(f, 3);
		total_read = read_varlong30(f, 3);
		stats.total_size = read_varlong30(f, 3);
		if (protocol_version >= 29) {
			stats.flist_buildtime = read_varlong30(f, 3);
			stats.flist_xfertime = read_varlong30(f, 3);
		}
	} else if (write_batch) {
		/* The --read-batch process is going to be a client
		 * receiver, so we need to give it the stats. */
		write_varlong30(batch_fd, total_read, 3);
		write_varlong30(batch_fd, total_written, 3);
		write_varlong30(batch_fd, stats.total_size, 3);
		if (protocol_version >= 29) {
			write_varlong30(batch_fd, stats.flist_buildtime, 3);
			write_varlong30(batch_fd, stats.flist_xfertime, 3);
		}
	}
}