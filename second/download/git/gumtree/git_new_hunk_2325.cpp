}

static int advertise_shallow_grafts_cb(const struct commit_graft *graft, void *cb)
{
	struct strbuf *sb = cb;
	if (graft->nr_parent == -1)
		packet_buf_write(sb, "shallow %s\n", oid_to_hex(&graft->oid));
	return 0;
}

static void advertise_shallow_grafts_buf(struct strbuf *sb)
{
	if (!is_repository_shallow())
