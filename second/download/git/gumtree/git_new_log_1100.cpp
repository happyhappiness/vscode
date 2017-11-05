error("cannot unpack %s from %s at offset %"PRIuMAX"",
				    oid_to_hex(entries[i].oid.oid), p->pack_name,
				    (uintmax_t)entries[i].offset);