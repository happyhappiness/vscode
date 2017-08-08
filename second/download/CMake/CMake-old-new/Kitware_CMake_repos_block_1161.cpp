{
	int i, number_slots;

	archive_check_magic(&a->archive,
	    ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
	    "__archive_read_register_format");

	number_slots = sizeof(a->formats) / sizeof(a->formats[0]);

	for (i = 0; i < number_slots; i++) {
		if (a->formats[i].bid == bid)
			return (ARCHIVE_WARN); /* We've already installed */
		if (a->formats[i].bid == NULL) {
			a->formats[i].bid = bid;
			a->formats[i].options = options;
			a->formats[i].read_header = read_header;
			a->formats[i].read_data = read_data;
			a->formats[i].read_data_skip = read_data_skip;
			a->formats[i].seek_data = seek_data;
			a->formats[i].cleanup = cleanup;
			a->formats[i].data = format_data;
			a->formats[i].name = name;
			a->formats[i].format_capabilties = format_capabilities;
			a->formats[i].has_encrypted_entries = has_encrypted_entries;
			return (ARCHIVE_OK);
		}
	}

	archive_set_error(&a->archive, ENOMEM,
	    "Not enough slots for format registration");
	return (ARCHIVE_FATAL);
}