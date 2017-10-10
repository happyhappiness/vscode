warning("Not updating %s"
				" (new tip %s does not contain %s)",
				b->name, oid_to_hex(&b->oid),
				oid_to_hex(&old_oid));