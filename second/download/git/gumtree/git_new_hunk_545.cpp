}

static int advertise_shallow_grafts_cb(const struct commit_graft *graft, void *cb)
{
	int fd = *(int *)cb;
	if (graft->nr_parent == -1)
		packet_write_fmt(fd, "shallow %s\n", oid_to_hex(&graft->oid));
	return 0;
}

void advertise_shallow_grafts(int fd)
{
	if (!is_repository_shallow())
