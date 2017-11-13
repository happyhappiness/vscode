error("index CRC mismatch for object %s "
					    "from %s at offset %"PRIuMAX"",
					    oid_to_hex(entries[i].oid.oid),
					    p->pack_name, (uintmax_t)offset);