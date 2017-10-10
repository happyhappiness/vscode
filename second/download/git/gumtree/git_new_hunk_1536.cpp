
	memset(&io, 0, sizeof(io));
	io.io.getline = rerere_file_getline;
	io.input = fopen(path, "r");
	io.io.wrerror = 0;
	if (!io.input)
		return error_errno("Could not open %s", path);

	if (output) {
		io.io.output = fopen(output, "w");
		if (!io.io.output) {
			error_errno("Could not write %s", output);
			fclose(io.input);
			return -1;
		}
	}

	hunk_no = handle_path(sha1, (struct rerere_io *)&io, marker_size);

	fclose(io.input);
