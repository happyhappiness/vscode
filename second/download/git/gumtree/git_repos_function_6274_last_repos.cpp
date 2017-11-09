static void drop_reused_delta(struct object_entry *entry)
{
	struct object_entry **p = &entry->delta->delta_child;
	struct object_info oi = OBJECT_INFO_INIT;

	while (*p) {
		if (*p == entry)
			*p = (*p)->delta_sibling;
		else
			p = &(*p)->delta_sibling;
	}
	entry->delta = NULL;
	entry->depth = 0;

	oi.sizep = &entry->size;
	oi.typep = &entry->type;
	if (packed_object_info(entry->in_pack, entry->in_pack_offset, &oi) < 0) {
		/*
		 * We failed to get the info from this pack for some reason;
		 * fall back to sha1_object_info, which may find another copy.
		 * And if that fails, the error will be recorded in entry->type
		 * and dealt with in prepare_pack().
		 */
		entry->type = sha1_object_info(entry->idx.oid.hash,
					       &entry->size);
	}
}