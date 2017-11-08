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

		contents = read_sha1_file(sha1, &type, &size);
		if (!contents)
			die("object %s disappeared", sha1_to_hex(sha1));
		if (type != data->type)
			die("object %s changed type!?", sha1_to_hex(sha1));
		if (data->info.sizep && size != data->size)
			die("object %s changed size!?", sha1_to_hex(sha1));

		write_or_die(fd, contents, size);
		free(contents);
	}
}