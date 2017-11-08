static void prune_refs(struct files_ref_store *refs, struct ref_to_prune *r)
{
	while (r) {
		prune_ref(refs, r);
		r = r->next;
	}
}