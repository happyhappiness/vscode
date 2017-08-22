{
	struct unknown_tag *tag;

#if DEBUG
	fprintf(stderr, "unknowntag_end:%s\n", name);
#endif
	tag = xar->unknowntags;
	if (tag == NULL || name == NULL)
		return;
	if (strcmp(tag->name.s, name) == 0) {
		xar->unknowntags = tag->next;
		archive_string_free(&(tag->name));
		free(tag);
		if (xar->unknowntags == NULL)
			xar->xmlsts = xar->xmlsts_unknown;
	}
}

