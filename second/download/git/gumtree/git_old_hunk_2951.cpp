		const char *name = pending->name;
		const char *path = pending->path;
		if (obj->flags & (UNINTERESTING | SEEN))
			continue;
		if (obj->type == OBJ_TAG) {
			obj->flags |= SEEN;
			show_object(obj, name, data);
			continue;
		}
		if (!path)
			path = "";
		if (obj->type == OBJ_TREE) {
			process_tree(revs, (struct tree *)obj, show_object,
				     &base, path, data);
			continue;
		}
		if (obj->type == OBJ_BLOB) {
			process_blob(revs, (struct blob *)obj, show_object,
				     &base, path, data);
			continue;
		}
		die("unknown pending object %s (%s)",
		    sha1_to_hex(obj->sha1), name);
	}
	object_array_clear(&revs->pending);
	strbuf_release(&base);
}
