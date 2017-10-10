
	for (i = 0; i < nr_objects; i++) {
		struct object_entry *obj = &objects[i];
		if (obj->real_type != OBJ_BAD)
			continue;
		obj->real_type = obj->type;
		sha1_object(NULL, obj, obj->size, obj->type, obj->idx.sha1);
		nr_delays--;
	}
	if (nr_delays)
		die(_("confusion beyond insanity in parse_pack_objects()"));
}

