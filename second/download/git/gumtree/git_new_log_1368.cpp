die("Failed to load %s %s into notes tree "
				    "from %s",
				    type == PTR_TYPE_NOTE ? "note" : "subtree",
				    oid_to_hex(&l->key_oid), t->ref);