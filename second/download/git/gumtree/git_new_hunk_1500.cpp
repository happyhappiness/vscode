
	if ((flag & REF_ISSYMREF) && (flag & REF_ISBROKEN)) {
		warning("symbolic ref is dangling: %s", path);
		return 0;
	}

	object = parse_object_or_die(oid, path);
	add_pending_object(revs, object, "");

	return 0;
}

/*
