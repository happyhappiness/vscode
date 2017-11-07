error("Object %s is a %s, not a commit or tree",
	      oid_to_hex(&oid), typename(obj->type));