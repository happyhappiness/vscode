
		if (c->object.flags & BOTTOM)
			continue;

		if (parse_commit(c))
			die("unable to parse commit %s",
			    oid_to_hex(&c->object.oid));

		for (p = c->parents; p; p = p->next) {
			uint32_t **p_refs = ref_bitmap_at(&info->ref_bitmap,
							  p->item);
			if (p->item->object.flags & SEEN)
				continue;
