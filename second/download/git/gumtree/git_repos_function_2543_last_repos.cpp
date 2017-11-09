static int emit_diff_first_parent_only(struct diff_options *opt, struct combine_diff_path *p)
{
	struct combine_diff_parent *p0 = &p->parent[0];
	if (p->mode && p0->mode) {
		opt->change(opt, p0->mode, p->mode, &p0->oid, &p->oid,
			1, 1, p->path, 0, 0);
	}
	else {
		const struct object_id *oid;
		unsigned int mode;
		int addremove;

		if (p->mode) {
			addremove = '+';
			oid = &p->oid;
			mode = p->mode;
		} else {
			addremove = '-';
			oid = &p0->oid;
			mode = p0->mode;
		}

		opt->add_remove(opt, addremove, mode, oid, 1, p->path, 0);
	}

	return 0;	/* we are done with p */
}