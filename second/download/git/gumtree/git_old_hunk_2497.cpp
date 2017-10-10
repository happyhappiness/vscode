
	expand_atom(sb, start + 1, end - start - 1, data);

	return end - start + 1;
}

static void print_object_or_die(int fd, struct expand_data *data)
{
	const unsigned char *sha1 = data->sha1;

	assert(data->info.typep);

	if (data->type == OBJ_BLOB) {
		if (stream_blob_to_fd(fd, sha1, NULL, 0) < 0)
			die("unable to stream %s to stdout", sha1_to_hex(sha1));
	}
	else {
		enum object_type type;
		unsigned long size;
		void *contents;
