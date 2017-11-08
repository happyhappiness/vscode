static void loosen_unused_packed_objects(struct rev_info *revs)
{
	struct packed_git *p;
	uint32_t i;
	struct object_id oid;

	for (p = packed_git; p; p = p->next) {
		if (!p->pack_local || p->pack_keep)
			continue;

		if (open_pack_index(p))
			die("cannot open pack index");

		for (i = 0; i < p->num_objects; i++) {
			nth_packed_object_oid(&oid, p, i);
			if (!packlist_find(&to_pack, oid.hash, NULL) &&
			    !has_sha1_pack_kept_or_nonlocal(oid.hash) &&
			    !loosened_object_can_be_discarded(&oid, p->mtime))
				if (force_object_loose(oid.hash, p->mtime))
					die("unable to force loose object");
		}
	}
}