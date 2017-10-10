			off_t offset = entries[i].offset;
			off_t len = entries[i+1].offset - offset;
			unsigned int nr = entries[i].nr;
			if (check_pack_crc(p, w_curs, offset, len, nr))
				err = error("index CRC mismatch for object %s "
					    "from %s at offset %"PRIuMAX"",
					    oid_to_hex(entries[i].oid.oid),
					    p->pack_name, (uintmax_t)offset);
		}

		curpos = entries[i].offset;
		type = unpack_object_header(p, w_curs, &curpos, &size);
		unuse_pack(w_curs);
