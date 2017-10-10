
 fail:
	send_client_data(3, abort_msg, sizeof(abort_msg));
	die("git upload-pack: %s", abort_msg);
}

static int got_oid(const char *hex, struct object_id *oid)
{
	struct object *o;
	int we_knew_they_have = 0;

	if (get_oid_hex(hex, oid))
		die("git upload-pack: expected SHA1 object, got '%s'", hex);
	if (!has_object_file(oid))
		return -1;

	o = parse_object(oid);
	if (!o)
		die("oops (%s)", oid_to_hex(oid));
	if (o->type == OBJ_COMMIT) {
		struct commit_list *parents;
		struct commit *commit = (struct commit *)o;
		if (o->flags & THEY_HAVE)
			we_knew_they_have = 1;
		else
