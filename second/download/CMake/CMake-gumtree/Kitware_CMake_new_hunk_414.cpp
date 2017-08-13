{
	struct unknown_tag *tag;

	tag = malloc(sizeof(*tag));
	if (tag == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
