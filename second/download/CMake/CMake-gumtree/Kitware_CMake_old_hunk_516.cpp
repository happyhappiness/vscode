		zip->end_of_entry = 1;

	/* Set up a more descriptive format name. */
	snprintf(zip->format_name, sizeof(zip->format_name), "ZIP %d.%d (%s)",
	    version / 10, version % 10,
	    compression_name(zip->entry->compression));
	a->archive.archive_format_name = zip->format_name;

	return (ret);
}

/*
 * Read "uncompressed" data.  There are three cases:
 *  1) We know the size of the data.  This is always true for the
