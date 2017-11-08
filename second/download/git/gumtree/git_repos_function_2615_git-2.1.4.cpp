static int git_rerere_gc_config(const char *var, const char *value, void *cb)
{
	struct rerere_gc_config_cb *cf = cb;

	if (!strcmp(var, "gc.rerereresolved"))
		cf->cutoff_resolve = git_config_int(var, value);
	else if (!strcmp(var, "gc.rerereunresolved"))
		cf->cutoff_noresolve = git_config_int(var, value);
	else
		return git_default_config(var, value, cb);
	return 0;
}