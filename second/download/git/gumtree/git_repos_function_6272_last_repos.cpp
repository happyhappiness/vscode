static void check_object(struct object_entry *entry)
{
	if (entry->in_pack) {
		struct packed_git *p = entry->in_pack;
		struct pack_window *w_curs = NULL;
		const unsigned char *base_ref = NULL;
		struct object_entry *base_entry;
		unsigned long used, used_0;
		unsigned long avail;
		off_t ofs;
		unsigned char *buf, c;

		buf = use_pack(p, &w_curs, entry->in_pack_offset, &avail);

		/*
		 * We want in_pack_type even if we do not reuse delta
		 * since non-delta representations could still be reused.
		 */
		used = unpack_object_header_buffer(buf, avail,
						   &entry->in_pack_type,
						   &entry->size);
		if (used == 0)
			goto give_up;

		/*
		 * Determine if this is a delta and if so whether we can
		 * reuse it or not.  Otherwise let's find out as cheaply as
		 * possible what the actual type and size for this object is.
		 */
		switch (entry->in_pack_type) {
		default:
			/* Not a delta hence we've already got all we need. */
			entry->type = entry->in_pack_type;
			entry->in_pack_header_size = used;
			if (entry->type < OBJ_COMMIT || entry->type > OBJ_BLOB)
				goto give_up;
			unuse_pack(&w_curs);
			return;
		case OBJ_REF_DELTA:
			if (reuse_delta && !entry->preferred_base)
				base_ref = use_pack(p, &w_curs,
						entry->in_pack_offset + used, NULL);
			entry->in_pack_header_size = used + 20;
			break;
		case OBJ_OFS_DELTA:
			buf = use_pack(p, &w_curs,
				       entry->in_pack_offset + used, NULL);
			used_0 = 0;
			c = buf[used_0++];
			ofs = c & 127;
			while (c & 128) {
				ofs += 1;
				if (!ofs || MSB(ofs, 7)) {
					error("delta base offset overflow in pack for %s",
					      oid_to_hex(&entry->idx.oid));
					goto give_up;
				}
				c = buf[used_0++];
				ofs = (ofs << 7) + (c & 127);
			}
			ofs = entry->in_pack_offset - ofs;
			if (ofs <= 0 || ofs >= entry->in_pack_offset) {
				error("delta base offset out of bound for %s",
				      oid_to_hex(&entry->idx.oid));
				goto give_up;
			}
			if (reuse_delta && !entry->preferred_base) {
				struct revindex_entry *revidx;
				revidx = find_pack_revindex(p, ofs);
				if (!revidx)
					goto give_up;
				base_ref = nth_packed_object_sha1(p, revidx->nr);
			}
			entry->in_pack_header_size = used + used_0;
			break;
		}

		if (base_ref && (base_entry = packlist_find(&to_pack, base_ref, NULL))) {
			/*
			 * If base_ref was set above that means we wish to
			 * reuse delta data, and we even found that base
			 * in the list of objects we want to pack. Goodie!
			 *
			 * Depth value does not matter - find_deltas() will
			 * never consider reused delta as the base object to
			 * deltify other objects against, in order to avoid
			 * circular deltas.
			 */
			entry->type = entry->in_pack_type;
			entry->delta = base_entry;
			entry->delta_size = entry->size;
			entry->delta_sibling = base_entry->delta_child;
			base_entry->delta_child = entry;
			unuse_pack(&w_curs);
			return;
		}

		if (entry->type) {
			/*
			 * This must be a delta and we already know what the
			 * final object type is.  Let's extract the actual
			 * object size from the delta header.
			 */
			entry->size = get_size_from_delta(p, &w_curs,
					entry->in_pack_offset + entry->in_pack_header_size);
			if (entry->size == 0)
				goto give_up;
			unuse_pack(&w_curs);
			return;
		}

		/*
		 * No choice but to fall back to the recursive delta walk
		 * with sha1_object_info() to find about the object type
		 * at this point...
		 */
		give_up:
		unuse_pack(&w_curs);
	}

	entry->type = sha1_object_info(entry->idx.oid.hash, &entry->size);
	/*
	 * The error condition is checked in prepare_pack().  This is
	 * to permit a missing preferred base object to be ignored
	 * as a preferred base.  Doing so can result in a larger
	 * pack file, but the transfer will still take place.
	 */
}