static int handle_file(const char *path, unsigned char *sha1, const char *output)
{
	int hunk_no = 0;
	struct rerere_io_file io;
	int marker_size = ll_merge_marker_size(path);

	memset(&io, 0, sizeof(io));
	io.io.getline = rerere_file_getline;
	io.input = fopen(path, "r");
	io.io.wrerror = 0;
	if (!io.input)
		return error("Could not open %s", path);

	if (output) {
		io.io.output = fopen(output, "w");
		if (!io.io.output) {
			fclose(io.input);
			return error("Could not write %s", output);
		}
	}

	hunk_no = handle_path(sha1, (struct rerere_io *)&io, marker_size);

	fclose(io.input);
	if (io.io.wrerror)
		error("There were errors while writing %s (%s)",
		      path, strerror(io.io.wrerror));
	if (io.io.output && fclose(io.io.output))
		io.io.wrerror = error_errno("Failed to flush %s", path);

	if (hunk_no < 0) {
		if (output)
			unlink_or_warn(output);
		return error("Could not parse conflict hunks in %s", path);
	}
	if (io.io.wrerror)
		return -1;
	return hunk_no;
}