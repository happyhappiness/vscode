static void parse_from_existing(struct branch *b)
{
	if (is_null_oid(&b->oid)) {
		oidclr(&b->branch_tree.versions[0].oid);
		oidclr(&b->branch_tree.versions[1].oid);
	} else {
		unsigned long size;
		char *buf;

		buf = read_object_with_reference(b->oid.hash,
						 commit_type, &size,
						 b->oid.hash);
		parse_from_commit(b, buf, size);
		free(buf);
	}
}