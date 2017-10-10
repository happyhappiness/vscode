		struct object *object = extra_refs.items[i].util;
		switch (object->type) {
		case OBJ_TAG:
			handle_tag(name, (struct tag *)object);
			break;
		case OBJ_COMMIT:
			/* create refs pointing to already seen commits */
			commit = (struct commit *)object;
			printf("reset %s\nfrom :%d\n\n", name,
			       get_object_mark(&commit->object));
			show_progress();
			break;
