die("Failed to load %s %s into notes tree "
				    "from %s",
				    type == PTR_TYPE_NOTE ? "note" : "subtree",
				    sha1_to_hex(l->key_sha1), t->ref);