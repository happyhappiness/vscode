static void do_server_recv(int f_in, int f_out, int argc,char *argv[])
{
	int exit_code;
	struct file_list *flist;
	char *local_name = NULL;
	char *dir = NULL;
	int save_verbose = verbose;

	if (filesfrom_fd >= 0) {
		/* We can't mix messages with files-from data on the socket,
		 * so temporarily turn off verbose messages. */
		verbose = 0;
	}

	if (verbose > 2) {
		rprintf(FINFO, "server_recv(%d) starting pid=%ld\n",
			argc, (long)getpid());
	}

	if (am_daemon && lp_read_only(module_id)) {
		rprintf(FERROR,"ERROR: module is read only\n");
		exit_cleanup(RERR_SYNTAX);
		return;
	}

	if (argc > 0) {
		dir = argv[0];
		argc--;
		argv++;
		if (!am_daemon && !push_dir(dir, 0)) {
			rsyserr(FERROR, errno, "push_dir#4 %s failed",
				full_fname(dir));
			exit_cleanup(RERR_FILESELECT);
		}
	}

	io_start_buffering_in();
	recv_filter_list(f_in);

	if (filesfrom_fd >= 0) {
		/* We need to send the files-from names to the sender at the
		 * same time that we receive the file-list from them, so we
		 * need the IO routines to automatically write out the names
		 * onto our f_out socket as we read the file-list.  This
		 * avoids both deadlock and extra delays/buffers. */
		io_set_filesfrom_fds(filesfrom_fd, f_out);
		filesfrom_fd = -1;
	}

	flist = recv_file_list(f_in);
	verbose = save_verbose;
	if (!flist) {
		rprintf(FERROR,"server_recv: recv_file_list error\n");
		exit_cleanup(RERR_FILESELECT);
	}
	the_file_list = flist;

	if (argc > 0)
		local_name = get_local_name(flist,argv[0]);

	/* Now that we know what our destination directory turned out to be,
	 * we can sanitize the --link-/copy-/compare-dest args correctly. */
	if (sanitize_paths) {
		char **dir;
		for (dir = basis_dir; *dir; dir++) {
			*dir = sanitize_path(NULL, *dir, NULL, curr_dir_depth, NULL);
		}
		if (partial_dir) {
			partial_dir = sanitize_path(NULL, partial_dir, NULL, curr_dir_depth, NULL);
		}
	}
	fix_basis_dirs();

	if (server_filter_list.head) {
		char **dir;
		struct filter_list_struct *elp = &server_filter_list;

		for (dir = basis_dir; *dir; dir++) {
			if (check_filter(elp, *dir, 1) < 0)
				goto options_rejected;
		}
		if (partial_dir && *partial_dir == '/'
		 && check_filter(elp, partial_dir, 1) < 0) {
		    options_rejected:
			rprintf(FERROR,
				"Your options have been rejected by the server.\n");
			exit_cleanup(RERR_SYNTAX);
		}
	}

	exit_code = do_recv(f_in,f_out,flist,local_name);
	exit_cleanup(exit_code);
}