void fast_export_init(int fd)
{
	first_commit_done = 0;
	if (buffer_fdinit(&report_buffer, fd))
		die_errno("cannot read from file descriptor %d", fd);
}