	unlink(rerere_path(name, "thisimage"));
	unlink(rerere_path(name, "preimage"));
	unlink(rerere_path(name, "postimage"));
	rmdir(git_path("rr-cache/%s", name));
}

struct rerere_gc_config_cb {
	int cutoff_noresolve;
	int cutoff_resolve;
};

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

void rerere_gc(struct string_list *rr)
{
	struct string_list to_remove = STRING_LIST_INIT_DUP;
	DIR *dir;
	struct dirent *e;
	int i, cutoff;
	time_t now = time(NULL), then;
	struct rerere_gc_config_cb cf = { 15, 60 };

	git_config(git_rerere_gc_config, &cf);
	dir = opendir(git_path("rr-cache"));
	if (!dir)
		die_errno("unable to open rr-cache directory");
	while ((e = readdir(dir))) {
		if (is_dot_or_dotdot(e->d_name))
			continue;

		then = rerere_last_used_at(e->d_name);
		if (then) {
			cutoff = cf.cutoff_resolve;
		} else {
			then = rerere_created_at(e->d_name);
			if (!then)
				continue;
			cutoff = cf.cutoff_noresolve;
		}
		if (then < now - cutoff * 86400)
			string_list_append(&to_remove, e->d_name);
	}
	closedir(dir);
	for (i = 0; i < to_remove.nr; i++)
