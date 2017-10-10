
	fd = create_tmpfile(&tmp_file, filename);
	if (fd < 0) {
		if (errno == EACCES)
			return error("insufficient permission for adding an object to repository database %s", get_object_directory());
		else
			return error_errno("unable to create temporary file");
	}

	/* Set it up */
	git_deflate_init(&stream, zlib_compression_level);
	stream.next_out = compressed;
	stream.avail_out = sizeof(compressed);
