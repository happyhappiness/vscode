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
						oid_to_hex(&object->oid));
				register_shallow(object->oid.hash);
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
					oid_to_hex(&object->oid));
				object->flags &= ~CLIENT_SHALLOW;
				/* make sure the real parents are parsed */
				unregister_shallow(object->oid.hash);
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
			register_shallow(object->oid.hash);
		}
		packet_flush(1);
	} else
		if (shallows.nr > 0) {
			int i;
			for (i = 0; i < shallows.nr; i++)
				register_shallow(shallows.objects[i].item->oid.hash);
		}

