{
	struct unknown_tag *tag;

#if DEBUG
	fprintf(stderr, "unknowntag_start:%s\n", name);
#endif
	tag = malloc(sizeof(*tag));
	if (tag == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
		return (ARCHIVE_FATAL);
	}
	tag->next = xar->unknowntags;
	archive_string_init(&(tag->name));
	archive_strcpy(&(tag->name), name);
	if (xar->unknowntags == NULL) {
		xar->xmlsts_unknown = xar->xmlsts;
		xar->xmlsts = UNKNOWN;
	}
	xar->unknowntags = tag;
	return (ARCHIVE_OK);
}