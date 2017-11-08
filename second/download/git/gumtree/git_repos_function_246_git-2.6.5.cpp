static void test_show_object(struct object *object,
			     const struct name_path *path,
			     const char *last, void *data)
{
	struct bitmap_test_data *tdata = data;
	int bitmap_pos;

	bitmap_pos = bitmap_position(object->sha1);
	if (bitmap_pos < 0)
		die("Object not in bitmap: %s\n", sha1_to_hex(object->sha1));

	bitmap_set(tdata->base, bitmap_pos);
	display_progress(tdata->prg, ++tdata->seen);
}