				count += p->num_objects;
			}
			stop_progress(&progress);
		}
	}

	heads = 0;
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		unsigned char sha1[20];
		if (!get_sha1(arg, sha1)) {
			struct object *obj = lookup_object(sha1);

			if (!obj || !(obj->flags & HAS_OBJ)) {
				error("%s: object missing", sha1_to_hex(sha1));
				errors_found |= ERROR_OBJECT;
				continue;
			}

			obj->used = 1;
			if (name_objects)
				add_decoration(fsck_walk_options.object_names,
					obj, xstrdup(arg));
			mark_object_reachable(obj);
			heads++;
			continue;
		}
		error("invalid parameter: expected sha1, got '%s'", arg);
		errors_found |= ERROR_OBJECT;
	}

