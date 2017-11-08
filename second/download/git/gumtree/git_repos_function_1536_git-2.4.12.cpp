static int fsck_tag(struct tag *tag, const char *data,
	unsigned long size, fsck_error error_func)
{
	struct object *tagged = tag->tagged;

	if (!tagged)
		return error_func(&tag->object, FSCK_ERROR, "could not load tagged object");

	return fsck_tag_buffer(tag, data, size, error_func);
}