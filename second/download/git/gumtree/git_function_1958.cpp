static int advertise_shallow_grafts_cb(const struct commit_graft *graft, void *cb)
{
	struct strbuf *sb = cb;
	if (graft->nr_parent == -1)
		packet_buf_write(sb, "shallow %s\n", sha1_to_hex(graft->sha1));
	return 0;
}