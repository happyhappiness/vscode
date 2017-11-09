void install_packed_git(struct packed_git *pack)
{
	if (pack->pack_fd != -1)
		pack_open_fds++;

	pack->next = packed_git;
	packed_git = pack;
}