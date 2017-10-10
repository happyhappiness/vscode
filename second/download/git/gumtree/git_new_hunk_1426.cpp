{
	if (sha1file_truncate(pack_file, checkpoint))
		die_errno("cannot truncate pack to skip duplicate");
	pack_size = checkpoint->offset;
}

static void stream_blob(uintmax_t len, struct object_id *oidout, uintmax_t mark)
{
	size_t in_sz = 64 * 1024, out_sz = 64 * 1024;
	unsigned char *in_buf = xmalloc(in_sz);
	unsigned char *out_buf = xmalloc(out_sz);
	struct object_entry *e;
	struct object_id oid;
	unsigned long hdrlen;
	off_t offset;
	git_SHA_CTX c;
	git_zstream s;
	struct sha1file_checkpoint checkpoint;
	int status = Z_OK;
