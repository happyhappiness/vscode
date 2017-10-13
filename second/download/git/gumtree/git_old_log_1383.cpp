error("cannot unpack %s from %s at offset %"PRIuMAX"",
				    sha1_to_hex(entries[i].sha1), p->pack_name,
				    (uintmax_t)entries[i].offset);