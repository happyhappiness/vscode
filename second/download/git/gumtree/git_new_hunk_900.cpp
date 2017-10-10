	struct strbuf out = STRBUF_INIT;
	strbuf_addf(&out, "anonymous blob %d", counter++);
	*size = out.len;
	return strbuf_detach(&out, NULL);
}

static void export_blob(const struct object_id *oid)
{
	unsigned long size;
	enum object_type type;
	char *buf;
	struct object *object;
	int eaten;

	if (no_data)
		return;

	if (is_null_oid(oid))
		return;

	object = lookup_object(oid->hash);
	if (object && object->flags & SHOWN)
		return;

	if (anonymize) {
		buf = anonymize_blob(&size);
		object = (struct object *)lookup_blob(oid->hash);
		eaten = 0;
	} else {
		buf = read_sha1_file(oid->hash, &type, &size);
		if (!buf)
			die ("Could not read blob %s", oid_to_hex(oid));
		if (check_sha1_signature(oid->hash, buf, size, typename(type)) < 0)
			die("sha1 mismatch in blob %s", oid_to_hex(oid));
		object = parse_object_buffer(oid->hash, type, size, buf, &eaten);
	}

	if (!object)
		die("Could not read blob %s", oid_to_hex(oid));

	mark_next_object(object);

	printf("blob\nmark :%"PRIu32"\ndata %lu\n", last_idnum, size);
	if (size && fwrite(buf, size, 1, stdout) != 1)
		die_errno ("Could not write blob '%s'", oid_to_hex(oid));
	printf("\n");

	show_progress();

	object->flags |= SHOWN;
	if (!eaten)
