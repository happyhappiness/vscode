		obj->type = type;
		return obj;
	}
	else {
		if (!quiet)
			error("object %s is a %s, not a %s",
			      sha1_to_hex(obj->sha1),
			      typename(obj->type), typename(type));
		return NULL;
	}
}

struct object *lookup_unknown_object(const unsigned char *sha1)
