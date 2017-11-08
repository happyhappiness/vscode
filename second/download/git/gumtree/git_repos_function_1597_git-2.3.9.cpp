static int open_packed_git(struct packed_git *p)
{
	if (!open_packed_git_1(p))
		return 0;
	if (p->pack_fd != -1) {
		close(p->pack_fd);
		pack_open_fds--;
		p->pack_fd = -1;
	}
	return -1;
}