static void print_object_or_die(struct batch_options *opt, struct expand_data *data)
{
	const struct object_id *oid = &data->oid;

	assert(data->info.typep);

	if (data->type == OBJ_BLOB) {
		if (opt->buffer_output)
			fflush(stdout);
		if (opt->cmdmode) {
			char *contents;
			unsigned long size;

			if (!data->rest)
				die("missing path for '%s'", oid_to_hex(oid));

			if (opt->cmdmode == 'w') {
				if (filter_object(data->rest, 0100644, oid,
						  &contents, &size))
					die("could not convert '%s' %s",
					    oid_to_hex(oid), data->rest);
			} else if (opt->cmdmode == 'c') {
				enum object_type type;
				if (!textconv_object(data->rest, 0100644, oid,
						     1, &contents, &size))
					contents = read_sha1_file(oid->hash, &type,
								  &size);
				if (!contents)
					die("could not convert '%s' %s",
					    oid_to_hex(oid), data->rest);
			} else
				die("BUG: invalid cmdmode: %c", opt->cmdmode);
			batch_write(opt, contents, size);
			free(contents);
		} else if (stream_blob_to_fd(1, oid, NULL, 0) < 0)
			die("unable to stream %s to stdout", oid_to_hex(oid));
	}
	else {
		enum object_type type;
		unsigned long size;
		void *contents;

		contents = read_sha1_file(oid->hash, &type, &size);
		if (!contents)
			die("object %s disappeared", oid_to_hex(oid));
		if (type != data->type)
			die("object %s changed type!?", oid_to_hex(oid));
		if (data->info.sizep && size != data->size)
			die("object %s changed size!?", oid_to_hex(oid));

		batch_write(opt, contents, size);
		free(contents);
	}
}