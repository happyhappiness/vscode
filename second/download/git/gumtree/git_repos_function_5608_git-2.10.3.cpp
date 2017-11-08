static int grep_sha1(struct grep_opt *opt, const unsigned char *sha1,
		     const char *filename, int tree_name_len,
		     const char *path)
{
	struct strbuf pathbuf = STRBUF_INIT;

	if (opt->relative && opt->prefix_length) {
		quote_path_relative(filename + tree_name_len, opt->prefix, &pathbuf);
		strbuf_insert(&pathbuf, 0, filename, tree_name_len);
	} else {
		strbuf_addstr(&pathbuf, filename);
	}

#ifndef NO_PTHREADS
	if (num_threads) {
		add_work(opt, GREP_SOURCE_SHA1, pathbuf.buf, path, sha1);
		strbuf_release(&pathbuf);
		return 0;
	} else
#endif
	{
		struct grep_source gs;
		int hit;

		grep_source_init(&gs, GREP_SOURCE_SHA1, pathbuf.buf, path, sha1);
		strbuf_release(&pathbuf);
		hit = grep_source(opt, &gs);

		grep_source_clear(&gs);
		return hit;
	}
}