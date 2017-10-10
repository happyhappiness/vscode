			if (check_pack_crc(p, &w_curs, obj_offset, len, revidx->nr)) {
				const unsigned char *sha1 =
					nth_packed_object_sha1(p, revidx->nr);
				error("bad packed object CRC for %s",
				      sha1_to_hex(sha1));
				mark_bad_packed_object(p, sha1);
				unuse_pack(&w_curs);
				return NULL;
			}
		}

		type = unpack_object_header(p, &w_curs, &curpos, &size);
		if (type != OBJ_OFS_DELTA && type != OBJ_REF_DELTA)
			break;
