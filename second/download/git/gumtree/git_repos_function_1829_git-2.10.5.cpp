static void close_pack(struct packed_git *p)
{
	close_pack_windows(p);
	close_pack_fd(p);
	close_pack_index(p);
}