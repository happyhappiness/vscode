
	if (!buf)
		die("git cat-file %s: bad file", obj_name);

	write_or_die(1, buf, size);
	free(buf);
	free(obj_context.path);
	return 0;
}

struct expand_data {
	struct object_id oid;
	enum object_type type;
