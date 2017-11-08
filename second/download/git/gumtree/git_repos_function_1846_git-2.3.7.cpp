static int emit_diff_first_parent_only(struct diff_options *opt, struct combine_diff_path *p)
{
	struct combine_diff_parent *p0 = &p->parent[0];
	if (p->mode && p0->mode) {
		opt->change(opt, p0->mode, p->mode, p0->sha1, p->sha1,
			1, 1, p->path, 0, 0);
	}
	else {
		const unsigned char *sha1;
		unsigned int mode;
		int addremove;

		if (p->mode) {
			addremove = '+';
			sha1 = p->sha1;
			mode = p->mode;
		} else {
			addremove = '-';
			sha1 = p0->sha1;
			mode = p0->mode;
		}

		opt->add_remove(opt, addremove, mode, sha1, 1, p->path, 0);
	}

	return 0;	/* we are done with p */
}