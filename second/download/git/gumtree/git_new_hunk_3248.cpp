	argv_array_clear(&argv);
	sha1_array_clear(&ref_tips_before_fetch);
	sha1_array_clear(&ref_tips_after_fetch);
	initialized_fetch_ref_tips = 0;
}

struct submodule_parallel_fetch {
	int count;
	struct argv_array args;
	const char *work_tree;
	const char *prefix;
	int command_line_option;
	int quiet;
	int result;
};
#define SPF_INIT {0, ARGV_ARRAY_INIT, NULL, NULL, 0, 0, 0}

static int get_next_submodule(struct child_process *cp,
			      struct strbuf *err, void *data, void **task_cb)
{
	int ret = 0;
	struct submodule_parallel_fetch *spf = data;

	for (; spf->count < active_nr; spf->count++) {
		struct strbuf submodule_path = STRBUF_INIT;
		struct strbuf submodule_git_dir = STRBUF_INIT;
		struct strbuf submodule_prefix = STRBUF_INIT;
		const struct cache_entry *ce = active_cache[spf->count];
		const char *git_dir, *default_argv;
		const struct submodule *submodule;

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		submodule = submodule_from_path(null_sha1, ce->name);
		if (!submodule)
			submodule = submodule_from_name(null_sha1, ce->name);

		default_argv = "yes";
		if (spf->command_line_option == RECURSE_SUBMODULES_DEFAULT) {
			if (submodule &&
			    submodule->fetch_recurse !=
						RECURSE_SUBMODULES_NONE) {
				if (submodule->fetch_recurse ==
						RECURSE_SUBMODULES_OFF)
					continue;
