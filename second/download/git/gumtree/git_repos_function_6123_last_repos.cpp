static void *run(void *arg)
{
	int hit = 0;
	struct grep_opt *opt = arg;

	while (1) {
		struct work_item *w = get_work();
		if (!w)
			break;

		opt->output_priv = w;
		if (w->source.type == GREP_SOURCE_SUBMODULE)
			hit |= grep_submodule_launch(opt, &w->source);
		else
			hit |= grep_source(opt, &w->source);
		grep_source_clear_data(&w->source);
		work_done(w);
	}
	free_grep_patterns(arg);
	free(arg);

	return (void*) (intptr_t) hit;
}