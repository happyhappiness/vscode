	archive_string_init(&(tag->name));
	archive_strcpy(&(tag->name), name);
	if (xar->unknowntags == NULL) {
#if DEBUG
		fprintf(stderr, "UNKNOWNTAG_START:%s\n", name);
#endif
		xar->xmlsts_unknown = xar->xmlsts;
		xar->xmlsts = UNKNOWN;
	}
