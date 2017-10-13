static int advertise_shallow_grafts_cb(const struct commit_graft *graft, void *cb)
{
	int fd = *(int *)cb;
	if (graft->nr_parent == -1)
		packet_write(fd, "shallow %s\n", sha1_to_hex(graft->sha1));
	return 0;
}