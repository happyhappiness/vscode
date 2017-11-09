int parse_sha1_header(const char *hdr, unsigned long *sizep)
{
	struct object_info oi = OBJECT_INFO_INIT;

	oi.sizep = sizep;
	return parse_sha1_header_extended(hdr, &oi, 0);
}