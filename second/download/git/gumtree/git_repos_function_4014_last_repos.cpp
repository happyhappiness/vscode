static void tmp_objdir_free(struct tmp_objdir *t)
{
	strbuf_release(&t->path);
	argv_array_clear(&t->env);
	free(t);
}