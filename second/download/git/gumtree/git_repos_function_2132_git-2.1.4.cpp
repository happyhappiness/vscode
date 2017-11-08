static void process_tag(struct tag *tag, struct object_array *p,
			const char *name, struct connectivity_progress *cp)
{
	struct object *obj = &tag->object;

	if (obj->flags & SEEN)
		return;
	obj->flags |= SEEN;
	update_progress(cp);

	if (parse_tag(tag) < 0)
		die("bad tag object %s", sha1_to_hex(obj->sha1));
	if (tag->tagged)
		add_object(tag->tagged, p, NULL, name);
}