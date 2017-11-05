static unsigned check_object(struct object *obj)
{
	if (!obj)
		return 0;

	if (!(obj->flags & FLAG_LINK))
		return 0;

	if (!(obj->flags & FLAG_CHECKED)) {
		unsigned long size;
		int type = sha1_object_info(obj->sha1, &size);
		if (type <= 0)
			die(_("did not receive expected object %s"),
			      sha1_to_hex(obj->sha1));
		if (type != obj->type)
			die(_("object %s: expected type %s, found %s"),
			    sha1_to_hex(obj->sha1),
			    typename(obj->type), typename(type));
		obj->flags |= FLAG_CHECKED;
		return 1;
	}

	return 0;
}