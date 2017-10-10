}

struct tag *lookup_tag(const unsigned char *sha1)
{
	struct object *obj = lookup_object(sha1);
	if (!obj)
		return create_object(sha1, alloc_tag_node());
	return object_as_type(obj, OBJ_TAG, 0);
}

static unsigned long parse_tag_date(const char *buf, const char *tail)
{
	const char *dateptr;

