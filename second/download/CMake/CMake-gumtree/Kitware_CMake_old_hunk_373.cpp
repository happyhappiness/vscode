{
	struct unknown_tag *tag;

#if DEBUG
	fprintf(stderr, "unknowntag_start:%s\n", name);
#endif
	tag = malloc(sizeof(*tag));
	if (tag == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
