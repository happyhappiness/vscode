static void do_server_sender(int f_in, int f_out, int argc, char *argv[])
{
	struct file_list *flist;
	char *dir = argv[0];

	if (DEBUG_GTE(SEND, 1))
		rprintf(FINFO, "server_sender starting pid=%d\n", (int)getpid());

	if (am_daemon && lp_write_only(module_id)) {
		rprintf(FERROR, "ERROR: module is write only\n");
		exit_cleanup(RERR_SYNTAX);
		return;
	}
	if (am_daemon && read_only && remove_source_files) {
		rprintf(FERROR,
		    "ERROR: --remove-%s-files cannot be used with a read-only module\n",
		    remove_source_files == 1 ? "source" : "sent");
		exit_cleanup(RERR_SYNTAX);
		return;
	}

	if (!relative_paths) {
		if (!change_dir(dir, CD_NORMAL)) {
			rsyserr(FERROR, errno, "change_dir#3 %s failed",
				full_fname(dir));
			exit_cleanup(RERR_FILESELECT);
		}
	}
	argc--;
	argv++;

	if (argc == 0 && (recurse || xfer_dirs || list_only)) {
		argc = 1;
		argv--;
		argv[0] = ".";
	}

	flist = send_file_list(f_out,argc,argv);
	if (!flist || flist->used == 0) {
		/* Make sure input buffering is off so we can't hang in noop_io_until_death(). */
		io_end_buffering_in(0);
		/* TODO:  we should really exit in a more controlled manner. */
		exit_cleanup(0);
	}

	io_start_buffering_in(f_in);

	send_files(f_in, f_out);
	io_flush(FULL_FLUSH);
	handle_stats(f_out);
	if (protocol_version >= 24)
		read_final_goodbye(f_in, f_out);
	io_flush(FULL_FLUSH);
	exit_cleanup(0);
}