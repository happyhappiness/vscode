static int
archive_read_format_cab_read_header(struct archive_read *a,
    struct archive_entry *entry)
{
	struct cab *cab;
	struct cfheader *hd;
	struct cffolder *prev_folder;
	struct cffile *file;
	struct archive_string_conv *sconv;
	int err = ARCHIVE_OK, r;
	
	cab = (struct cab *)(a->format->data);
	if (cab->found_header == 0) {
		err = cab_read_header(a); 
		if (err < ARCHIVE_WARN)
			return (err);
		/* We've found the header. */
		cab->found_header = 1;
	}
	hd = &cab->cfheader;

	if (hd->file_index >= hd->file_count) {
		cab->end_of_archive = 1;
		return (ARCHIVE_EOF);
	}
	file = &hd->file_array[hd->file_index++];

	cab->end_of_entry = 0;
	cab->end_of_entry_cleanup = 0;
	cab->entry_compressed_bytes_read = 0;
	cab->entry_uncompressed_bytes_read = 0;
	cab->entry_unconsumed = 0;
	cab->entry_cffile = file;

	/*
	 * Choose a proper folder.
	 */
	prev_folder = cab->entry_cffolder;
	switch (file->folder) {
	case iFoldCONTINUED_FROM_PREV:
	case iFoldCONTINUED_PREV_AND_NEXT:
		cab->entry_cffolder = &hd->folder_array[0];
		break;
	case iFoldCONTINUED_TO_NEXT:
		cab->entry_cffolder = &hd->folder_array[hd->folder_count-1];
		break;
	default:
		cab->entry_cffolder = &hd->folder_array[file->folder];
		break;
	}
	/* If a cffolder of this file is changed, reset a cfdata to read
	 * file contents from next cfdata. */
	if (prev_folder != cab->entry_cffolder)
		cab->entry_cfdata = NULL;

	/* If a pathname is UTF-8, prepare a string conversion object
	 * for UTF-8 and use it. */
	if (file->attr & ATTR_NAME_IS_UTF) {
		if (cab->sconv_utf8 == NULL) {
			cab->sconv_utf8 =
			    archive_string_conversion_from_charset(
				&(a->archive), "UTF-8", 1);
			if (cab->sconv_utf8 == NULL)
				return (ARCHIVE_FATAL);
		}
		sconv = cab->sconv_utf8;
	} else if (cab->sconv != NULL) {
		/* Choose the conversion specified by the option. */
		sconv = cab->sconv;
	} else {
		/* Choose the default conversion. */
		if (!cab->init_default_conversion) {
			cab->sconv_default =
			    archive_string_default_conversion_for_read(
			      &(a->archive));
			cab->init_default_conversion = 1;
		}
		sconv = cab->sconv_default;
	}

	/*
	 * Set a default value and common data
	 */
	r = cab_convert_path_separator_1(&(file->pathname), file->attr);
	if (archive_entry_copy_pathname_l(entry, file->pathname.s,
	    archive_strlen(&(file->pathname)), sconv) != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Pathname cannot be converted "
		    "from %s to current locale.",
		    archive_string_conversion_charset_name(sconv));
		err = ARCHIVE_WARN;
	}
	if (r < 0) {
		/* Convert a path separator '\' -> '/' */
		cab_convert_path_separator_2(cab, entry);
	}

	archive_entry_set_size(entry, file->uncompressed_size);
	if (file->attr & ATTR_RDONLY)
		archive_entry_set_mode(entry, AE_IFREG | 0555);
	else
		archive_entry_set_mode(entry, AE_IFREG | 0666);
	archive_entry_set_mtime(entry, file->mtime, 0);

	cab->entry_bytes_remaining = file->uncompressed_size;
	cab->entry_offset = 0;
	/* We don't need compress data. */
	if (file->uncompressed_size == 0)
		cab->end_of_entry_cleanup = cab->end_of_entry = 1;

	/* Set up a more descriptive format name. */
	sprintf(cab->format_name, "CAB %d.%d (%s)",
	    hd->major, hd->minor, cab->entry_cffolder->compname);
	a->archive.archive_format_name = cab->format_name;

	return (err);
}