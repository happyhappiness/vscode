static void drop_origin_blob(struct origin *o)
{
	if (o->file.ptr) {
		free(o->file.ptr);
		o->file.ptr = NULL;
	}
}