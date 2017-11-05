static void receive_needs(void)
{
	struct object_array shallows = OBJECT_ARRAY_INIT;
	int depth = 0;
	int has_non_tip = 0;

	shallow_nr = 0;
	for (;;) {
		struct object *o;
		const char *features;
		unsigned char sha1_buf[20];
		char *line = packet_read_line(0, NULL);
		reset_timeout();
		if (!line)
			break;

		if (starts_with(line, "shallow ")) {
			unsigned char sha1[20];
			struct object *object;
			if (get_sha1_hex(line + 8, sha1))
				die("invalid shallow line: %s", line);
			object = parse_object(sha1);
			if (!object)
				continue;
			if (object->type != OBJ_COMMIT)
				die("invalid shallow object %s", sha1_to_hex(sha1));
			if (!(object->flags & CLIENT_SHALLOW)) {
				object->flags |= CLIENT_SHALLOW;
				add_object_array(object, NULL, &shallows);
			}
			continue;
		}
		if (starts_with(line, "deepen ")) {
			char *end;
			depth = strtol(line + 7, &end, 0);
			if (end == line + 7 || depth <= 0)
				die("Invalid deepen: %s", line);
			continue;
		}
		if (!starts_with(line, "want ") ||
		    get_sha1_hex(line+5, sha1_buf))
			die("git upload-pack: protocol error, "
			    "expected to get sha, not '%s'", line);

		features = line + 45;

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

		o = parse_object(sha1_buf);
		if (!o)
			die("git upload-pack: not our ref %s",
			    sha1_to_hex(sha1_buf));
		if (!(o->flags & WANTED)) {
			o->flags |= WANTED;
			if (!is_our_ref(o))
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

	if (depth == 0 && shallows.nr == 0)
		return;
	if (depth > 0) {
		struct commit_list *result = NULL, *backup = NULL;
		int i;
		if (depth == INFINITE_DEPTH && !is_repository_shallow())
			for (i = 0; i < shallows.nr; i++) {
				struct object *object = shallows.objects[i].item;
				object->flags |= NOT_SHALLOW;
			}
		else
			backup = result =
				get_shallow_commits(&want_obj, depth,
						    SHALLOW, NOT_SHALLOW);
		while (result) {
			struct object *object = &result->item->object;
			if (!(object->flags & (CLIENT_SHALLOW|NOT_SHALLOW))) {
				packet_write(1, "shallow %s",
						sha1_to_hex(object->sha1));
				register_shallow(object->sha1);
				shallow_nr++;
			}
			result = result->next;
		}
		free_commit_list(backup);
		for (i = 0; i < shallows.nr; i++) {
			struct object *object = shallows.objects[i].item;
			if (object->flags & NOT_SHALLOW) {
				struct commit_list *parents;
				packet_write(1, "unshallow %s",
					sha1_to_hex(object->sha1));
				object->flags &= ~CLIENT_SHALLOW;
				/* make sure the real parents are parsed */
				unregister_shallow(object->sha1);
				object->parsed = 0;
				parse_commit_or_die((struct commit *)object);
				parents = ((struct commit *)object)->parents;
				while (parents) {
					add_object_array(&parents->item->object,
							NULL, &want_obj);
					parents = parents->next;
				}
				add_object_array(object, NULL, &extra_edge_obj);
			}
			/* make sure commit traversal conforms to client */
			register_shallow(object->sha1);
		}
		packet_flush(1);
	} else
		if (shallows.nr > 0) {
			int i;
			for (i = 0; i < shallows.nr; i++)
				register_shallow(shallows.objects[i].item->sha1);
		}

	shallow_nr += shallows.nr;
	free(shallows.objects);
}