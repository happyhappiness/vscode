		return;

	/*
	 * If it is a tag object, see if we use a value that derefs
	 * the object, and if we do grab the object it refers to.
	 */
	tagged = &((struct tag *)obj)->tagged->oid;

	/*
	 * NEEDSWORK: This derefs tag only once, which
	 * is good to deal with chains of trust, but
	 * is not consistent with what deref_tag() does
	 * which peels the onion to the core.
	 */
	buf = get_obj(tagged, &obj, &size, &eaten);
	if (!buf)
		die(_("missing object %s for %s"),
		    oid_to_hex(tagged), ref->refname);
	if (!obj)
		die(_("parse_object_buffer failed on %s for %s"),
		    oid_to_hex(tagged), ref->refname);
	grab_values(ref->value, 1, obj, buf, size);
	if (!eaten)
		free(buf);
}

/*
