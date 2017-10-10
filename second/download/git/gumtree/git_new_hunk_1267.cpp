	object = lookup_object(oid->hash);
	if (object && object->flags & SHOWN)
		return;

	if (anonymize) {
		buf = anonymize_blob(&size);
		object = (struct object *)lookup_blob(oid);
		eaten = 0;
	} else {
		buf = read_sha1_file(oid->hash, &type, &size);
		if (!buf)
			die ("Could not read blob %s", oid_to_hex(oid));
		if (check_sha1_signature(oid->hash, buf, size, typename(type)) < 0)
			die("sha1 mismatch in blob %s", oid_to_hex(oid));
		object = parse_object_buffer(oid, type, size, buf, &eaten);
	}

	if (!object)
		die("Could not read blob %s", oid_to_hex(oid));

	mark_next_object(object);
