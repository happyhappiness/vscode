error("Object %s is a %s, not a commit or tree",
	      sha1_to_hex(sha1), typename(obj->type));