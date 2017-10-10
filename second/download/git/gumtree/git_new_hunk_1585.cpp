static void receive_needs(void)
{
	struct object_array shallows = OBJECT_ARRAY_INIT;
	struct string_list deepen_not = STRING_LIST_INIT_DUP;
	int depth = 0;
	int has_non_tip = 0;
	timestamp_t deepen_since = 0;
	int deepen_rev_list = 0;

	shallow_nr = 0;
	for (;;) {
		struct object *o;
		const char *features;
		struct object_id oid_buf;
		char *line = packet_read_line(0, NULL);
		const char *arg;

		reset_timeout();
		if (!line)
			break;

		if (skip_prefix(line, "shallow ", &arg)) {
			struct object_id oid;
			struct object *object;
			if (get_oid_hex(arg, &oid))
				die("invalid shallow line: %s", line);
			object = parse_object(&oid);
			if (!object)
				continue;
			if (object->type != OBJ_COMMIT)
				die("invalid shallow object %s", oid_to_hex(&oid));
			if (!(object->flags & CLIENT_SHALLOW)) {
				object->flags |= CLIENT_SHALLOW;
				add_object_array(object, NULL, &shallows);
			}
			continue;
		}
