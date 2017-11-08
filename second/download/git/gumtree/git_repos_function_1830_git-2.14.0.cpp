static struct object_entry *parse_treeish_dataref(const char **p)
{
	struct object_id oid;
	struct object_entry *e;

	if (**p == ':') {	/* <mark> */
		e = find_mark(parse_mark_ref_space(p));
		if (!e)
			die("Unknown mark: %s", command_buf.buf);
		oidcpy(&oid, &e->idx.oid);
	} else {	/* <sha1> */
		if (parse_oid_hex(*p, &oid, p))
			die("Invalid dataref: %s", command_buf.buf);
		e = find_object(&oid);
		if (*(*p)++ != ' ')
			die("Missing space after tree-ish: %s", command_buf.buf);
	}

	while (!e || e->type != OBJ_TREE)
		e = dereference(e, &oid);
	return e;
}