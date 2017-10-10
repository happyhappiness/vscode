		if (obj->type == OBJ_TAG) {
			obj->flags |= SEEN;
			p = add_one_object(obj, p);
			continue;
		}
		if (obj->type == OBJ_TREE) {
			p = process_tree((struct tree *)obj, p);
			continue;
		}
		if (obj->type == OBJ_BLOB) {
			p = process_blob((struct blob *)obj, p);
			continue;
		}
		die("unknown pending object %s (%s)", sha1_to_hex(obj->sha1), name);
	}

	while (objects) {
