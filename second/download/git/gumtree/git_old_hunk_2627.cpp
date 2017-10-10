		die_errno("unable to overwrite old ref-pack file");

	prune_refs(cbdata.ref_to_prune);
	return 0;
}

int repack_without_refs(struct string_list *refnames, struct strbuf *err)
{
	struct ref_dir *packed;
	struct string_list_item *refname;
	int ret, needs_repacking = 0, removed = 0;

	assert(err);
