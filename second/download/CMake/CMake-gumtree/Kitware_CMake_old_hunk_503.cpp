	archive_string_init(&(tag->name));

	archive_strcpy(&(tag->name), name);

	if (xar->unknowntags == NULL) {

		xar->xmlsts_unknown = xar->xmlsts;

		xar->xmlsts = UNKNOWN;

	}

