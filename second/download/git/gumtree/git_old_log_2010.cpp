error("object %s is a %s, not a %s",
			      sha1_to_hex(obj->sha1),
			      typename(obj->type), typename(type));