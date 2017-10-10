			base_from_cache = 1;
			break;
		}

		if (do_check_packed_object_crc && p->index_version > 1) {
			struct revindex_entry *revidx = find_pack_revindex(p, obj_offset);
			off_t len = revidx[1].offset - obj_offset;
			if (check_pack_crc(p, &w_curs, obj_offset, len, revidx->nr)) {
				const unsigned char *sha1 =
					nth_packed_object_sha1(p, revidx->nr);
				error("bad packed object CRC for %s",
				      sha1_to_hex(sha1));
				mark_bad_packed_object(p, sha1);
