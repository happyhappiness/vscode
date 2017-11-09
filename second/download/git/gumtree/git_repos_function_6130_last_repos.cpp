static int grep_oid(struct grep_opt *opt, const struct object_id *oid,
		     const char *filename, int tree_name_len,
		     const char *path)
{
	struct strbuf pathbuf = STRBUF_INIT;

	if (super_prefix) {
		strbuf_add(&pathbuf, filename, tree_name_len);
		strbuf_addstr(&pathbuf, super_prefix);
		strbuf_addstr(&pathbuf, filename + tree_name_len);
	} else {
		strbuf_addstr(&pathbuf, filename);
	}

	if (opt->relative && opt->prefix_length) {
		char *name = strbuf_detach(&pathbuf, NULL);
		quote_path_relative(name + tree_name_len, opt->prefix, &pathbuf);
		strbuf_insert(&pathbuf, 0, name, tree_name_len);
		free(name);
	}

#ifndef NO_PTHREADS
	if (num_threads) {
		add_work(opt, GREP_SOURCE_OID, pathbuf.buf, path, oid);
		strbuf_release(&pathbuf);
		return 0;
	} else
#endif
	{
		struct grep_source gs;
		int hit;

		grep_source_init(&gs, GREP_SOURCE_OID, pathbuf.buf, path, oid);
		strbuf_release(&pathbuf);
		hit = grep_source(opt, &gs);

		grep_source_clear(&gs);
		return hit;
	}
}