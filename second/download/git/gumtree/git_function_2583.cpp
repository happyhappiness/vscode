static int loosen_small_pack(const struct packed_git *p)
{
	struct child_process unpack = CHILD_PROCESS_INIT;

	if (lseek(p->pack_fd, 0, SEEK_SET) < 0)
		die_errno("Failed seeking to start of '%s'", p->pack_name);

	unpack.in = p->pack_fd;
	unpack.git_cmd = 1;
	unpack.stdout_to_stderr = 1;
	argv_array_push(&unpack.args, "unpack-objects");
	if (!show_stats)
		argv_array_push(&unpack.args, "-q");

	return run_command(&unpack);
}