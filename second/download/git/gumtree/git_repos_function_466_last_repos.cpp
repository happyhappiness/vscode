static void drop_origin_blob(struct blame_origin *o)
{
	if (o->file.ptr) {
		FREE_AND_NULL(o->file.ptr);
	}
}