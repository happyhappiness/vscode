		return error(_("Could not spawn pack-objects"));

	for (i = 0; i < revs->pending.nr; i++) {
		struct object *object = revs->pending.objects[i].item;
		if (object->flags & UNINTERESTING)
			write_or_die(pack_objects.in, "^", 1);
		write_or_die(pack_objects.in, oid_to_hex(&object->oid), GIT_SHA1_HEXSZ);
		write_or_die(pack_objects.in, "\n", 1);
	}
	close(pack_objects.in);
	if (finish_command(&pack_objects))
		return error(_("pack-objects died"));
	return 0;
