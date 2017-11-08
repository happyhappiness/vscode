static void show_object(struct object *object, const char *name, void *data)
{
	struct bitmap *base = data;
	int bitmap_pos;

	bitmap_pos = bitmap_position(object->sha1);

	if (bitmap_pos < 0)
		bitmap_pos = ext_index_add_object(object, name);

	bitmap_set(base, bitmap_pos);
}