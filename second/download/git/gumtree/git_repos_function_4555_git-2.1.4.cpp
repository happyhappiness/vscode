static const char *unpack(int err_fd, struct shallow_info *si)
{
	struct pack_header hdr;
	struct argv_array av = ARGV_ARRAY_INIT;
	const char *hdr_err;
	int status;
	char hdr_arg[38];
	struct child_process child;
	int fsck_objects = (receive_fsck_objects >= 0
			    ? receive_fsck_objects
			    : transfer_fsck_objects >= 0
			    ? transfer_fsck_objects
			    : 0);

	hdr_err = parse_pack_header(&hdr);
	if (hdr_err) {
		if (err_fd > 0)
			close(err_fd);
		return hdr_err;
	}
	snprintf(hdr_arg, sizeof(hdr_arg),
			"--pack_header=%"PRIu32",%"PRIu32,
			ntohl(hdr.hdr_version), ntohl(hdr.hdr_entries));

	if (si->nr_ours || si->nr_theirs) {
		alt_shallow_file = setup_temporary_shallow(si->shallow);
		argv_array_pushl(&av, "--shallow-file", alt_shallow_file, NULL);
	}

	memset(&child, 0, sizeof(child));
	if (ntohl(hdr.hdr_entries) < unpack_limit) {
		argv_array_pushl(&av, "unpack-objects", hdr_arg, NULL);
		if (quiet)
			argv_array_push(&av, "-q");
		if (fsck_objects)
			argv_array_push(&av, "--strict");
		child.argv = av.argv;
		child.no_stdout = 1;
		child.err = err_fd;
		child.git_cmd = 1;
		status = run_command(&child);
		if (status)
			return "unpack-objects abnormal exit";
	} else {
		int s;
		char keep_arg[256];

		s = sprintf(keep_arg, "--keep=receive-pack %"PRIuMAX" on ", (uintmax_t) getpid());
		if (gethostname(keep_arg + s, sizeof(keep_arg) - s))
			strcpy(keep_arg + s, "localhost");

		argv_array_pushl(&av, "index-pack",
				 "--stdin", hdr_arg, keep_arg, NULL);
		if (fsck_objects)
			argv_array_push(&av, "--strict");
		if (fix_thin)
			argv_array_push(&av, "--fix-thin");
		child.argv = av.argv;
		child.out = -1;
		child.err = err_fd;
		child.git_cmd = 1;
		status = start_command(&child);
		if (status)
			return "index-pack fork failed";
		pack_lockfile = index_pack_lockfile(child.out);
		close(child.out);
		status = finish_command(&child);
		if (status)
			return "index-pack abnormal exit";
		reprepare_packed_git();
	}
	return NULL;
}