	return o;
}

static void origin_decref(struct origin *o)
{
	if (o && --o->refcnt <= 0) {
		if (o->previous)
			origin_decref(o->previous);
		free(o->file.ptr);
		free(o);
	}
}

static void drop_origin_blob(struct origin *o)
{
	if (o->file.ptr) {
