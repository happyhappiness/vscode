static void show_object(struct object *object, const struct name_path *path,
			const char *last, void *data)
{
	struct bitmap *base = data;
	bitmap_set(base, find_object_pos(object->sha1));
	mark_as_seen(object);
}