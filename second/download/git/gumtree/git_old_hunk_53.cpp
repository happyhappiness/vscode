}

struct tag *lookup_tag(const unsigned char *sha1)
{
	struct object *obj = lookup_object(sha1);
	if (!obj)
		return create_object(sha1, OBJ_TAG, alloc_tag_node());
	if (!obj->type)
		obj->type = OBJ_TAG;
	if (obj->type != OBJ_TAG) {
		error("Object %s is a %s, not a tag",
		      sha1_to_hex(sha1), typename(obj->type));
		return NULL;
	}
	return (struct tag *) obj;
}

static unsigned long parse_tag_date(const char *buf, const char *tail)
{
	const char *dateptr;

