static void write_remote_refs(const struct ref *local_refs)
{
	const struct ref *r;

	lock_packed_refs(LOCK_DIE_ON_ERROR);

	for (r = local_refs; r; r = r->next) {
		if (!r->peer_ref)
			continue;
		add_packed_ref(r->peer_ref->name, r->old_sha1);
	}

	if (commit_packed_refs())
		die_errno("unable to overwrite old ref-pack file");
}