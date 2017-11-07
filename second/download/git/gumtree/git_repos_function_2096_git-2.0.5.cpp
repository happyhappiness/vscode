static void process_blob(struct blob *blob,
			 struct object_array *p,
			 struct name_path *path,
			 const char *name,
			 struct connectivity_progress *cp)
{
	struct object *obj = &blob->object;

	if (!blob)
		die("bad blob object");
	if (obj->flags & SEEN)
		return;
	obj->flags |= SEEN;
	update_progress(cp);
	/* Nothing to do, really .. The blob lookup was the important part */
}