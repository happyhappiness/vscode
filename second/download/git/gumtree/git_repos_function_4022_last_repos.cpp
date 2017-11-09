struct tmp_objdir *tmp_objdir_create(void)
{
	static int installed_handlers;
	struct tmp_objdir *t;

	if (the_tmp_objdir)
		die("BUG: only one tmp_objdir can be used at a time");

	t = xmalloc(sizeof(*t));
	strbuf_init(&t->path, 0);
	argv_array_init(&t->env);

	strbuf_addf(&t->path, "%s/incoming-XXXXXX", get_object_directory());

	/*
	 * Grow the strbuf beyond any filename we expect to be placed in it.
	 * If tmp_objdir_destroy() is called by a signal handler, then
	 * we should be able to use the strbuf to remove files without
	 * having to call malloc.
	 */
	strbuf_grow(&t->path, 1024);

	if (!mkdtemp(t->path.buf)) {
		/* free, not destroy, as we never touched the filesystem */
		tmp_objdir_free(t);
		return NULL;
	}

	the_tmp_objdir = t;
	if (!installed_handlers) {
		atexit(remove_tmp_objdir);
		sigchain_push_common(remove_tmp_objdir_on_signal);
		installed_handlers++;
	}

	if (setup_tmp_objdir(t->path.buf)) {
		tmp_objdir_destroy(t);
		return NULL;
	}

	env_append(&t->env, ALTERNATE_DB_ENVIRONMENT,
		   absolute_path(get_object_directory()));
	env_replace(&t->env, DB_ENVIRONMENT, absolute_path(t->path.buf));
	env_replace(&t->env, GIT_QUARANTINE_ENVIRONMENT,
		    absolute_path(t->path.buf));

	return t;
}