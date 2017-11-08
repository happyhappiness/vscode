static void handle_stats(int f)
{
	endtime = time(NULL);

	/* Cache two stats because the read/write code can change it. */
	total_read = stats.total_read;
	total_written = stats.total_written;

	if (do_stats && verbose > 1) {
		/* These come out from every process */
		show_malloc_stats();
		show_flist_stats();
	}

	if (am_generator)
		return;

	if (am_daemon) {
		log_exit(0, __FILE__, __LINE__);
		if (f == -1 || !am_sender)
			return;
	}

	if (am_server) {
		if (am_sender) {
			write_longint(f, total_read);
			write_longint(f, total_written);
			write_longint(f, stats.total_size);
			if (protocol_version >= 29) {
				write_longint(f, stats.flist_buildtime);
				write_longint(f, stats.flist_xfertime);
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
		total_written = read_longint(f);
		total_read = read_longint(f);
		stats.total_size = read_longint(f);
		if (protocol_version >= 29) {
			stats.flist_buildtime = read_longint(f);
			stats.flist_xfertime = read_longint(f);
		}
	} else if (write_batch) {
		/* The --read-batch process is going to be a client
		 * receiver, so we need to give it the stats. */
		write_longint(batch_fd, total_read);
		write_longint(batch_fd, total_written);
		write_longint(batch_fd, stats.total_size);
		if (protocol_version >= 29) {
			write_longint(batch_fd, stats.flist_buildtime);
			write_longint(batch_fd, stats.flist_xfertime);
		}
	}
}