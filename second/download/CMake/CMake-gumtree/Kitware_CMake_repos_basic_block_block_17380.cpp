{
	const char *encname;
	int r;

	r = xmlwrite_fstring(a, writer, "length", "%ju", heap->length);
	if (r < 0)
		return (ARCHIVE_FATAL);
	r = xmlwrite_fstring(a, writer, "offset", "%ju", heap->temp_offset);
	if (r < 0)
		return (ARCHIVE_FATAL);
	r = xmlwrite_fstring(a, writer, "size", "%ju", heap->size);
	if (r < 0)
		return (ARCHIVE_FATAL);
	switch (heap->compression) {
	case GZIP:
		encname = "application/x-gzip"; break;
	case BZIP2:
		encname = "application/x-bzip2"; break;
	case LZMA:
		encname = "application/x-lzma"; break;
	case XZ:
		encname = "application/x-xz"; break;
	default:
		encname = "application/octet-stream"; break;
	}
	r = xmlwrite_string_attr(a, writer, "encoding", NULL,
	    "style", encname);
	if (r < 0)
		return (ARCHIVE_FATAL);
	r = xmlwrite_sum(a, writer, "archived-checksum", &(heap->a_sum));
	if (r < 0)
		return (ARCHIVE_FATAL);
	r = xmlwrite_sum(a, writer, "extracted-checksum", &(heap->e_sum));
	if (r < 0)
		return (ARCHIVE_FATAL);
	return (ARCHIVE_OK);
}