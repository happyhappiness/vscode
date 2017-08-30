	    ARCHIVE_STATE_NEW, "archive_read_support_format_tar");

	tar = (struct tar *)calloc(1, sizeof(*tar));
#ifdef HAVE_COPYFILE_H
	/* Set this by default on Mac OS. */
	tar->process_mac_extensions = 1;
#endif
	if (tar == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate tar data");
