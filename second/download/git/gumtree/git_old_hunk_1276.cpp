	if (read_loose_object(path, oid->hash, &type, &size, &contents) < 0)
		return NULL;

	if (!contents && type != OBJ_BLOB)
		die("BUG: read_loose_object streamed a non-blob");

	obj = parse_object_buffer(oid->hash, type, size, contents, &eaten);

	if (!eaten)
		free(contents);
	return obj;
}

