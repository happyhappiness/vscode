static int tmp_objdir_destroy_1(struct tmp_objdir *t, int on_signal)
{
	int err;

	if (!t)
		return 0;

	if (t == the_tmp_objdir)
		the_tmp_objdir = NULL;

	/*
	 * This may use malloc via strbuf_grow(), but we should
	 * have pre-grown t->path sufficiently so that this
	 * doesn't happen in practice.
	 */
	err = remove_dir_recursively(&t->path, 0);

	/*
	 * When we are cleaning up due to a signal, we won't bother
	 * freeing memory; it may cause a deadlock if the signal
	 * arrived while libc's allocator lock is held.
	 */
	if (!on_signal)
		tmp_objdir_free(t);
	return err;
}