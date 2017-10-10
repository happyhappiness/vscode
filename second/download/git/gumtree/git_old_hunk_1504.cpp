		if (v->s == NULL)
			goto need_obj;
	}
	return;

 need_obj:
	buf = get_obj(ref->objectname, &obj, &size, &eaten);
	if (!buf)
		die(_("missing object %s for %s"),
		    sha1_to_hex(ref->objectname), ref->refname);
	if (!obj)
		die(_("parse_object_buffer failed on %s for %s"),
		    sha1_to_hex(ref->objectname), ref->refname);

	grab_values(ref->value, 0, obj, buf, size);
	if (!eaten)
		free(buf);

	/*
