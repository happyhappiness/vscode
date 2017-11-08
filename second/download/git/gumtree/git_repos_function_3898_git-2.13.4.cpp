int tmp_objdir_migrate(struct tmp_objdir *t)
{
	struct strbuf src = STRBUF_INIT, dst = STRBUF_INIT;
	int ret;

	if (!t)
		return 0;

	strbuf_addbuf(&src, &t->path);
	strbuf_addstr(&dst, get_object_directory());

	ret = migrate_paths(&src, &dst);

	strbuf_release(&src);
	strbuf_release(&dst);

	tmp_objdir_destroy(t);
	return ret;
}