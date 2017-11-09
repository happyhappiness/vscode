static int read_file_or_gitlink(const struct cache_entry *ce, struct strbuf *buf)
{
	if (!ce)
		return 0;
	return read_blob_object(buf, &ce->oid, ce->ce_mode);
}