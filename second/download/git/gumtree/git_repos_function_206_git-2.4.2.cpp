static void show_object(struct object *object, const struct name_path *path,
			const char *last, void *data)
{
	struct bitmap *base = data;
	int bitmap_pos;

	bitmap_pos = bitmap_position(object->sha1);

	if (bitmap_pos < 0) {
		char *name = path_name(path, last);
		bitmap_pos = ext_index_add_object(object, name);
		free(name);
	}

	bitmap_set(base, bitmap_pos);
}