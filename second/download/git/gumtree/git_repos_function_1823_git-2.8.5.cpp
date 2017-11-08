int parse_sha1_header(const char *hdr, unsigned long *sizep)
{
	struct object_info oi;

	oi.sizep = sizep;
	oi.typename = NULL;
	oi.typep = NULL;
	return parse_sha1_header_extended(hdr, &oi, LOOKUP_REPLACE_OBJECT);
}