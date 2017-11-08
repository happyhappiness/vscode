static void write_global_extended_header(struct archiver_args *args)
{
	const unsigned char *sha1 = args->commit_sha1;
	struct strbuf ext_header = STRBUF_INIT;
	struct ustar_header header;
	unsigned int mode;

	if (sha1)
		strbuf_append_ext_header(&ext_header, "comment",
					 sha1_to_hex(sha1), 40);
	if (args->time > USTAR_MAX_MTIME) {
		strbuf_append_ext_header_uint(&ext_header, "mtime",
					      args->time);
		args->time = USTAR_MAX_MTIME;
	}

	if (!ext_header.len)
		return;

	memset(&header, 0, sizeof(header));
	*header.typeflag = TYPEFLAG_GLOBAL_HEADER;
	mode = 0100666;
	xsnprintf(header.name, sizeof(header.name), "pax_global_header");
	prepare_header(args, &header, mode, ext_header.len);
	write_blocked(&header, sizeof(header));
	write_blocked(ext_header.buf, ext_header.len);
	strbuf_release(&ext_header);
}