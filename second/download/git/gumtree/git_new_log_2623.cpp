fprintf(stderr, "Cannot obtain needed %s %s\n",
		obj->type ? typename(obj->type): "object",
		oid_to_hex(&obj->oid));