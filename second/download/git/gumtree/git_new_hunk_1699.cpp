		return;

	object = lookup_object(sha1);
	if (object && object->flags & SHOWN)
		return;

	if (anonymize) {
		buf = anonymize_blob(&size);
		object = (struct object *)lookup_blob(sha1);
		eaten = 0;
	} else {
		buf = read_sha1_file(sha1, &type, &size);
		if (!buf)
			die ("Could not read blob %s", sha1_to_hex(sha1));
		if (check_sha1_signature(sha1, buf, size, typename(type)) < 0)
			die("sha1 mismatch in blob %s", sha1_to_hex(sha1));
		object = parse_object_buffer(sha1, type, size, buf, &eaten);
	}

	if (!object)
		die("Could not read blob %s", sha1_to_hex(sha1));

	mark_next_object(object);

	printf("blob\nmark :%"PRIu32"\ndata %lu\n", last_idnum, size);
