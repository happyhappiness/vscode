	if (!(obj->flags & FLAG_LINK))
		return 0;

	if (!(obj->flags & FLAG_CHECKED)) {
		unsigned long size;
		int type = sha1_object_info(obj->sha1, &size);
		if (type != obj->type || type <= 0)
			die(_("object of unexpected type"));
		obj->flags |= FLAG_CHECKED;
		return 1;
	}

	return 0;
}
