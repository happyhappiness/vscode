		if (type != obj->type || type <= 0)
			die("object of unexpected type");
		obj->flags |= FLAG_WRITTEN;
		return 0;
	}

	obj_buf = lookup_object_buffer(obj);
	if (!obj_buf)
		die("Whoops! Cannot find object '%s'", sha1_to_hex(obj->sha1));
	if (fsck_object(obj, obj_buf->buffer, obj_buf->size, 1,
			fsck_error_function))
		die("Error in object");
	if (fsck_walk(obj, check_object, NULL))
		die("Error on reachable objects of %s", sha1_to_hex(obj->sha1));
	write_cached_object(obj, obj_buf);
	return 0;
}

static void write_rest(void)
{
	unsigned i;
