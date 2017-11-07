int read_tree_recursive(struct tree *tree,
			const char *base, int baselen,
			int stage, const struct pathspec *pathspec,
			read_tree_fn_t fn, void *context)
{
	struct strbuf sb = STRBUF_INIT;
	int ret;

	strbuf_add(&sb, base, baselen);
	ret = read_tree_1(tree, &sb, stage, pathspec, fn, context);
	strbuf_release(&sb);
	return ret;
}