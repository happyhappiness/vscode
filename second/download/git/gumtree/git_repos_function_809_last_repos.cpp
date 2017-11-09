static void write_extended_header(struct archiver_args *args,
				  const unsigned char *sha1,
				  const void *buffer, unsigned long size)
{
	struct ustar_header header;
	unsigned int mode;
	memset(&header, 0, sizeof(header));
	*header.typeflag = TYPEFLAG_EXT_HEADER;
	mode = 0100666;
	xsnprintf(header.name, sizeof(header.name), "%s.paxheader", sha1_to_hex(sha1));
	prepare_header(args, &header, mode, size);
	write_blocked(&header, sizeof(header));
	write_blocked(buffer, size);
}