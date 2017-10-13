die(_("object %s: expected type %s, found %s"),
			    sha1_to_hex(obj->sha1),
			    typename(obj->type), typename(type));