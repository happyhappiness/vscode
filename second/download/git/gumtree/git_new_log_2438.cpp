die(_("object %s: expected type %s, found %s"),
			    oid_to_hex(&obj->oid),
			    typename(obj->type), typename(type));