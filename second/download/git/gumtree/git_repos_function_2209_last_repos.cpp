static int open_packed_git(struct packed_git *p)
{
	if (!open_packed_git_1(p))
		return 0;
	close_pack_fd(p);
	return -1;
}