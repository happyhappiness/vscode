
	if (!(obj->flags & FLAG_LINK))
		return 0;

	if (!(obj->flags & FLAG_CHECKED)) {
		unsigned long size;
		int type = sha1_object_info(obj->oid.hash, &size);
		if (type <= 0)
			die(_("did not receive expected object %s"),
			      oid_to_hex(&obj->oid));
		if (type != obj->type)
			die(_("object %s: expected type %s, found %s"),
			    oid_to_hex(&obj->oid),
			    typename(obj->type), typename(type));
		obj->flags |= FLAG_CHECKED;
		return 1;
	}

	return 0;
