		hashcpy(sha1, e->idx.sha1);
	} else {	/* <sha1> */
		if (get_sha1_hex(*p, sha1))
			die("Invalid dataref: %s", command_buf.buf);
		e = find_object(sha1);
		*p += 40;
	}

	while (!e || e->type != OBJ_TREE)
		e = dereference(e, sha1);
	return e;
}
