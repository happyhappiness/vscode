static void write_tree_trivial(struct object_id *oid)
{
	if (write_cache_as_tree(oid->hash, 0, NULL))
		die(_("git write-tree failed to write a tree"));
}