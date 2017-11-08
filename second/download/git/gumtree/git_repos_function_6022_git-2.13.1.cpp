static int grep_file(struct grep_opt *opt, const char *filename)
{
	struct strbuf buf = STRBUF_INIT;

	if (super_prefix)
		strbuf_addstr(&buf, super_prefix);
	strbuf_addstr(&buf, filename);

	if (opt->relative && opt->prefix_length) {
		char *name = strbuf_detach(&buf, NULL);
		quote_path_relative(name, opt->prefix, &buf);
		free(name);
	}

#ifndef NO_PTHREADS
	if (num_threads) {
		add_work(opt, GREP_SOURCE_FILE, buf.buf, filename, filename);
		strbuf_release(&buf);
		return 0;
	} else
#endif
	{
		struct grep_source gs;
		int hit;

		grep_source_init(&gs, GREP_SOURCE_FILE, buf.buf, filename, filename);
		strbuf_release(&buf);
		hit = grep_source(opt, &gs);

		grep_source_clear(&gs);
		return hit;
	}
}