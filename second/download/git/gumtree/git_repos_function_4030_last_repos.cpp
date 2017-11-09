void tmp_objdir_add_as_alternate(const struct tmp_objdir *t)
{
	add_to_alternates_memory(t->path.buf);
}