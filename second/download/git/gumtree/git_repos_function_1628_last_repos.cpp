static void run_diffstat(struct diff_filepair *p, struct diff_options *o,
			 struct diffstat_t *diffstat)
{
	const char *name;
	const char *other;

	if (DIFF_PAIR_UNMERGED(p)) {
		/* unmerged */
		builtin_diffstat(p->one->path, NULL, NULL, NULL, diffstat, o, p);
		return;
	}

	name = p->one->path;
	other = (strcmp(name, p->two->path) ? p->two->path : NULL);

	if (o->prefix_length)
		strip_prefix(o->prefix_length, &name, &other);

	diff_fill_oid_info(p->one);
	diff_fill_oid_info(p->two);

	builtin_diffstat(name, other, p->one, p->two, diffstat, o, p);
}