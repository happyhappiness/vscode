			obj = &tag->object;
		}
	} else {
		warning("object %s has unknown type id %d", sha1_to_hex(sha1), type);
		obj = NULL;
	}
	return obj;
}

struct object *parse_object_or_die(const unsigned char *sha1,
				   const char *name)
{
