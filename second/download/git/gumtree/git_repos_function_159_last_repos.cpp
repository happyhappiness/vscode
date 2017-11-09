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
		if (skip_prefix(line, "deepen ", &arg)) {
			char *end = NULL;
			depth = strtol(arg, &end, 0);
			if (!end || *end || depth <= 0)
				die("Invalid deepen: %s", line);
			continue;
		}
		if (skip_prefix(line, "deepen-since ", &arg)) {
			char *end = NULL;
			deepen_since = parse_timestamp(arg, &end, 0);
			if (!end || *end || !deepen_since ||
			    /* revisions.c's max_age -1 is special */
			    deepen_since == -1)
				die("Invalid deepen-since: %s", line);
			deepen_rev_list = 1;
			continue;
		}
		if (skip_prefix(line, "deepen-not ", &arg)) {
			char *ref = NULL;
			struct object_id oid;
			if (expand_ref(arg, strlen(arg), oid.hash, &ref) != 1)
				die("git upload-pack: ambiguous deepen-not: %s", line);
			string_list_append(&deepen_not, ref);
			free(ref);
			deepen_rev_list = 1;
			continue;
		}
		if (!skip_prefix(line, "want ", &arg) ||
		    get_oid_hex(arg, &oid_buf))
			die("git upload-pack: protocol error, "
			    "expected to get sha, not '%s'", line);

		features = arg + 40;

		if (parse_feature_request(features, "deepen-relative"))
			deepen_relative = 1;
		if (parse_feature_request(features, "multi_ack_detailed"))
			multi_ack = 2;
		else if (parse_feature_request(features, "multi_ack"))
			multi_ack = 1;
		if (parse_feature_request(features, "no-done"))
			no_done = 1;
		if (parse_feature_request(features, "thin-pack"))
			use_thin_pack = 1;
		if (parse_feature_request(features, "ofs-delta"))
			use_ofs_delta = 1;
		if (parse_feature_request(features, "side-band-64k"))
			use_sideband = LARGE_PACKET_MAX;
		else if (parse_feature_request(features, "side-band"))
			use_sideband = DEFAULT_PACKET_MAX;
		if (parse_feature_request(features, "no-progress"))
			no_progress = 1;
		if (parse_feature_request(features, "include-tag"))
			use_include_tag = 1;

		o = parse_object(&oid_buf);
		if (!o) {
			packet_write_fmt(1,
					 "ERR upload-pack: not our ref %s",
					 oid_to_hex(&oid_buf));
			die("git upload-pack: not our ref %s",
			    oid_to_hex(&oid_buf));
		}
		if (!(o->flags & WANTED)) {
			o->flags |= WANTED;
			if (!((allow_unadvertised_object_request & ALLOW_ANY_SHA1) == ALLOW_ANY_SHA1
			      || is_our_ref(o)))
				has_non_tip = 1;
			add_object_array(o, NULL, &want_obj);
		}
	}

	/*
	 * We have sent all our refs already, and the other end
	 * should have chosen out of them. When we are operating
	 * in the stateless RPC mode, however, their choice may
	 * have been based on the set of older refs advertised
	 * by another process that handled the initial request.
	 */
	if (has_non_tip)
		check_non_tip();

	if (!use_sideband && daemon_mode)
		no_progress = 1;

	if (depth == 0 && !deepen_rev_list && shallows.nr == 0)
		return;
	if (depth > 0 && deepen_rev_list)
		die("git upload-pack: deepen and deepen-since (or deepen-not) cannot be used together");
	if (depth > 0)
		deepen(depth, deepen_relative, &shallows);
	else if (deepen_rev_list) {
		struct argv_array av = ARGV_ARRAY_INIT;
		int i;

		argv_array_push(&av, "rev-list");
		if (deepen_since)
			argv_array_pushf(&av, "--max-age=%"PRItime, deepen_since);
		if (deepen_not.nr) {
			argv_array_push(&av, "--not");
			for (i = 0; i < deepen_not.nr; i++) {
				struct string_list_item *s = deepen_not.items + i;
				argv_array_push(&av, s->string);
			}
			argv_array_push(&av, "--not");
		}
		for (i = 0; i < want_obj.nr; i++) {
			struct object *o = want_obj.objects[i].item;
			argv_array_push(&av, oid_to_hex(&o->oid));
		}
		deepen_by_rev_list(av.argc, av.argv, &shallows);
		argv_array_clear(&av);
	}
	else
		if (shallows.nr > 0) {
			int i;
			for (i = 0; i < shallows.nr; i++)
				register_shallow(&shallows.objects[i].item->oid);
		}

	shallow_nr += shallows.nr;
	free(shallows.objects);
}