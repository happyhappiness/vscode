		return 0;
	}

	obj_buf = lookup_object_buffer(obj);
	if (!obj_buf)
		die("Whoops! Cannot find object '%s'", sha1_to_hex(obj->sha1));
	if (fsck_object(obj, obj_buf->buffer, obj_buf->size, &fsck_options))
		die("Error in object");
	fsck_options.walk = check_object;
	if (fsck_walk(obj, NULL, &fsck_options))
		die("Error on reachable objects of %s", sha1_to_hex(obj->sha1));
	write_cached_object(obj, obj_buf);
	return 0;
}

static void write_rest(void)
{
	unsigned i;
	for (i = 0; i < nr_objects; i++) {
		if (obj_list[i].obj)
			check_object(obj_list[i].obj, OBJ_ANY, NULL, NULL);
	}
}

static void added_object(unsigned nr, enum object_type type,
			 void *data, unsigned long size);

