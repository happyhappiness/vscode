static void file_change_deleteall(struct branch *b)
{
	release_tree_content_recursive(b->branch_tree.tree);
	oidclr(&b->branch_tree.versions[0].oid);
	oidclr(&b->branch_tree.versions[1].oid);
	load_tree(&b->branch_tree);
	b->num_notes = 0;
}