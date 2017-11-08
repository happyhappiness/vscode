void cache_tree_write(struct strbuf *sb, struct cache_tree *root)
{
	write_one(sb, root, "", 0);
}